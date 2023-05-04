#include "SJsonParser.h"

inline void _sjs_copy(char *dest, char *start, char *end)
{
    for (; start <= end; ++start, ++dest)
        *dest = *start;
}

static inline void _sjs_setKey(SString *str, char *key, char *val, int padding)
{
    for (; padding > 0; padding--)
        sstr_appendc(str, ' ');
    sstr_appendc(str, '\"');
    sstr_appendcs(str, key);
    sstr_appendcs(str, "\":");
    if (*val == _SJS_STRING)
    {
        sstr_appendc(str, '\"');
        sstr_appendcs(str, val + 1);
        sstr_appendc(str, '\"');
    }
    else
        sstr_appendcs(str, val + 1);
    free(key);
    free(val);
}

static inline char *_sjs_parseOpen(char *p)
{
    for (; *p != null; ++p)
    {
        if (*p == '{')
            return p;
    }
    return p;
}

SQTree *sjs_loadFile(char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return null;
    }
    struct stat info;
    if (fstat(fd, &info) != 0)
    {
        perror("fstat");
        return null;
    }
    char buff[info.st_size + 1];
    read(fd, &buff, info.st_size);
    buff[info.st_size] = '\00';
    return sjs_parseString((char *)&buff);
}

void sjs_save(SQTree* json, char* file)
{
    FILE* f = fopen(file, "w");
    if (f == -1)
    {
        perror("open");
        exit(1);
    }
    SString*json_data = sjs_toString(json);
    write(f->_fileno, json_data->s_str, json_data->s_size);
    if (ftruncate(f->_fileno, json_data->s_size) == 1)
    {
        perror("ftruncate");
        exit(1);
    }
    sstr_delete(json_data);
    fclose(f);
}

void sjs_setPair(SQTree* json, char* key, JsonValueType value)
{
    sstr_createeOnStack(key_str);

    sstr_appendcs(key_str, key);

    switch(value.type)
    {
        case _SJS_STRING:
        {
            if(value.value._string == null)
            {
                char* value_str = (char *)malloc(7);
                _sjs_copy(value_str + 1, "null", "null" + 3);
                *(value_str + 5) = '\00';
                *value_str = _SJS_NULL;
                sqtr_setNoCopy(json, key_str->s_str, value_str);
                break;
            }
            sstr_createeOnStack(value_str);
            sstr_appendc(value_str, _SJS_STRING);
            sstr_appendcs(value_str, value.value._string);
            sstr_serialize(key_str);
            sstr_serialize(value_str);
            sqtr_setNoCopy(json, key_str->s_str, value_str->s_str);
            break;
        }
        case _SJS_EXTENDED_INT:
        {
            char* value_str = (char*) malloc(MAX_LENGTH_INT+2);
            *value_str = _SJS_NUM;
            sstr_serialize(key_str);
            *(value_str + convert_IntToCStr(value.value._int, value_str + 1)+1) = '\00';
            sqtr_setNoCopy(json, key_str->s_str, value_str);
            break;
        }
        case _SJS_EXTENDED_LONG:
        {
            char *value_str = (char *)malloc(MAX_LENGTH_LONG + 2);
            *value_str = _SJS_NUM;
            sstr_serialize(key_str);
            *(value_str + convert_LongToCStr(value.value._long, value_str + 1)+1) = '\00';
            sqtr_setNoCopy(json, key_str->s_str, value_str);
            break;
        }
        case _SJS_EXTENDED_DOUBLE:
        {
            char *value_str = (char *)malloc(MAX_LENGTH_FLOAT + 2);
            *value_str = _SJS_NUM;
            sstr_serialize(key_str);
            *(value_str + convert_DoubleToCStr(value.value._double, value_str + 1)+1) = '\00';
            sqtr_setNoCopy(json, key_str->s_str, value_str);
            break;
        }
        case _SJS_BOOL:
        {
            char *value_str;
            if (value.value._bool == 0)
            {
                value_str = (char *)malloc(7);
                _sjs_copy(value_str+1, "false", "false"+4);
                *(value_str + 6) = '\00';
            }
            else 
            {
                value_str = (char *)malloc(7);
                _sjs_copy(value_str + 1, "true", "true" + 3);
                *(value_str + 5) = '\00';
            }
            *value_str = _SJS_BOOL;
            sqtr_setNoCopy(json, key_str->s_str, value_str);
            break;
        }
        case _SJS_ARRAY:
        {
            sqtr_setNoCopy(json, key_str->s_str, sjs_arr_toCString(value.value._jsonArray));
            break;
        }
    }
}

static inline char *_sjs_parsePair(char *p, SQTree *json)
{
    for (; *p == ' ' || *p == ',' || *p == '"' || *p == '\n' || *p == '}' || *p == '{'; ++p)
        if (*p == 0)
            return p;

    /* get key */
    char *_start = p;
    for (; (*p) != '"'; p++)
        if (*p == 0)
            return p;
    char *_end = (p++) - 1;

    /* create key */
    char *key = (char *)malloc((_end - _start) + 2);
    _sjs_copy(key, _start, _end);

    /* get value */
    for (; *p == ' ' || *p == ':' || *p == '\n'; ++p)
        ; /* increment p until value starts*/
    int type = 0;
    /* switch through different possibilities */
    int c;
    switch (*p)
    {
    /* json as key */
    case '{':
        type = _SJS_JSON;
        _start = p;
        c = 1;
        for (++p;; ++p)
        {
            if (*p == 0)
                return p;
            else if (*p == '{')
                ++c;
            else if (*p == '}')
            {
                --c;
                if (c == 0)
                {
                    _end = p;
                    break;
                }
            }
        }
        break;
    /* array as key */
    case '[':
        type = _SJS_ARRAY;
        _start = p;
        for (; *p != ']'; ++p)
        {
            if (*p == 0)
                return p;
        }
        _end = p;
        break;

    /* strings with value true */
    case '"':
        type = _SJS_STRING;
        ++p;
        _start = p;
        for (; *p != '"'; ++p)
        {
            if (*p == 0)
                return p;
        }
        _end = p - 1;
        break;
    /* null */
    case 'n':
        type = _SJS_NULL;
        _start = "null";
        _end = ((char *)"null") + 3;
        p = p + 4;
        break;
    /* booleans with value false */
    case 'f':
        type = _SJS_BOOL;
        _start = "false";
        _end = ((char *)"false") + 4;
        p = p + 5;
        break;
    /* booleans with value true */
    case 't':
        type = _SJS_BOOL;
        _start = "true";
        _end = ((char *)"true") + 3;
        p = p + 4;
        break;
    /* numbers */
    default:
        type = _SJS_NUM;
        _start = p;
        for (; *p >= '0' && *p <= '9'; ++p)
            if (*p == 0)
                return p;
        _end = p-1;
        break;
    }

    /* create value */
    char *value = (char *)malloc((_end - _start) + 3 /* +2 to add type and \00 footer */);
    /* set value type */
    *value = type;
    _sjs_copy(value + 1, _start, _end);

    /* insert value to tree */
    sqtr_setNoCopy(json, key, value);
    /* increase p until row is over */
    for (; *p != ',' && *p != '}' && *p != 0; ++p);
    return p; /* return current state of p*/
}

/* get functions */
inline JsonValue sjs_getValue(SQTree *json, char *key)
{
    char *result = (char *)sqtr_get(json, key);
    JsonValue value;
    if (result == null)
    {
        printf("true\n");
        value._string = null;
        return value;
    }
    printf("%d\n",convert_getType(result));
    switch (*(result++))
    {
    case _SJS_NUM:
        /* examine exact number type */
        switch (convert_getType(result))
        {
        case NT_FLOAT:
            value._double = convert_CStrToDouble(result);
            return value;
        case NT_INT:
            value._int = convert_CStrToInt(result);
            return value;
        case NT_LONG:
            value._long = convert_CStrToLong(result);
            return value;
        case NT_NONE: /* check if number is false detected */
            value._string = null;
            return value;
        }
    case _SJS_STRING:
        value._string = result;
        return value;
    case _SJS_NULL:
        value._string = 0;
        return value;
    case _SJS_JSON:
        value._jsonData = sjs_parseString(result);
        return value;
    case _SJS_ARRAY:
        value._jsonArray = sjs_arr_parseString(result);
        return value;
    case _SJS_BOOL:
        value._bool = strcmp(result, "true") == 0;
        return value;
    default:
        value._string = null;
        return value;
    }
}

inline JsonValueType sjs_getValueAndType(SQTree *json, char *key)
{
    char *result = (char *)sqtr_get(json, key);
    JsonValueType type;
    if (result == null)
    {
        type.value._string = null;
        return type;
    }
    switch (*(result++))
    {
    case _SJS_NUM:
        /* examine exact number type */
        switch (convert_getType(result))
        {
        case NT_FLOAT:
            type.value._double = convert_CStrToDouble(result);
            type.type = _SJS_NUM;
            return type;
        case NT_INT:
            type.value._int = convert_CStrToInt(result);
            type.type = _SJS_NUM;
            return type;
        case NT_LONG:
            type.value._long = convert_CStrToLong(result);
            type.type = _SJS_NUM;
            return type;
        case NT_NONE: /* check if number is false detected */
            type.value._string = null;
            type.type = _SJS_NUM;
            return type;
        }
    case _SJS_STRING:
        type.value._string = result;
        type.type = _SJS_STRING;
        return type;
    case _SJS_NULL:
        type.value._string = 0;
        type.type = _SJS_NULL;
        return type;
    case _SJS_JSON:
        type.value._jsonData = sjs_parseString(result);
        type.type = _SJS_JSON;
        return type;
    case _SJS_ARRAY:
        type.value._jsonArray = sjs_arr_parseString(result);
        type.type = _SJS_ARRAY;
        return type;
    case _SJS_BOOL:
        type.value._bool = strcmp(result, "true") == 0;
        type.type = _SJS_BOOL;
        return type;
    default:
        type.value._string = null;
        type.type = _SJS_NULL;
        return type;
    }
}

SQTree *sjs_parseString(char *str)
{
    SQTree *json = sqtr_create();
    str = _sjs_parseOpen(str);
    for (; *str != null; ++str)
        str = _sjs_parsePair(str, json);
    return json;
}

SString *sjs_toString(SQTree *json)
{
    SString* res = sstr_createe();
    if (sqtr_empty(json))
    {   
        sstr_appends(res, "{}", 2);
        return res;
    }
    sstr_appendc(res, '{');
    for (SQNode *node = sqtr_popl(json);; node = sqtr_popl(json))
    {
        sstr_appendc(res, '\"');
        sstr_appendcs(res, node->key);
        sstr_appendcs(res, "\":");
        if (*node->value == _SJS_STRING)
        {
            sstr_appendc(res, '\"');
            sstr_appendcs(res, node->value + 1);
            sstr_appendc(res, '\"');
        }
        else
            sstr_appendcs(res, node->value + 1);
        free(node->key);
        free(node->value);
        free(node);
        if (sqtr_empty(json))
            break;
        else
            sstr_appendc(res, ',');
    }
    sstr_appendc(res, '}');
    free(json);
    return res;
}

char *sjs_toCString(SQTree *json)
{
    sstr_createeOnStack(res);
    sstr_appendc(res, _SJS_JSON);
    if (sqtr_empty(json))
    {
        sstr_appends(res, "{}", 2);
        return sstr_serialize(res);
    }
    sstr_appendc(res, '{');
    for (SQNode *node = sqtr_popl(json);; node = sqtr_popl(json))
    {
        sstr_appendc(res, '\"');
        sstr_appendcs(res, node->key);
        sstr_appendcs(res, "\":");
        if (*node->value == _SJS_STRING)
        {
            sstr_appendc(res, '\"');
            sstr_appendcs(res, node->value + 1);
            sstr_appendc(res, '\"');
        }
        else
            sstr_appendcs(res, node->value + 1);
        free(node->key);
        free(node->value);
        free(node);
        if (sqtr_empty(json))
            break;
        else
            sstr_appendc(res, ',');
    }
    sstr_appendc(res, '}');
    free(json);
    return sstr_serialize(res);
}

int sjs_appendElement(char *file, char *element, unsigned int size)
{
    int fd = open(file, O_RDWR);
    if (fd == 0)
        perror("open");
    struct stat info;
    if (fstat(fd, &info) != 0)
        perror("fstat");
    int pos = info.st_size;
find_pos:
    if (pos > 10)
    {
        char buff[11];
        lseek(fd, pos - 10, SEEK_SET);
        read(fd, &buff, 10);
        buff[10] = '\00';
        for (char *_buff = ((char *)&buff) + 11; *_buff != '}'; _buff--, pos--)
            if (_buff == (char *)&buff)
                goto find_pos;
        lseek(fd, pos, SEEK_SET);
        convert_dprintf(fd, "\n  ,%x\n}", element, size);
    }
    else
    {
        char buff[info.st_size + 1];
        lseek(fd, 0, SEEK_SET);
        read(fd, &buff, info.st_size);
        buff[info.st_size] = '\00';
        for (char *_buff = ((char *)&buff) + info.st_size; *_buff != '}'; _buff--, pos--)
            if (_buff == (char *)&buff)
                return -1;
        lseek(fd, pos, SEEK_SET);
        convert_dprintf(fd, "  %x\n}", element, size);
    }
    close(fd);
}