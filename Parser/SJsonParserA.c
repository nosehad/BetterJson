#include "SJsonParserA.h"

static inline char *_sjs_arr_getopen(char *str)
{
    for (; *str != '[' && *str != 0; ++str);
    return str + 1;
}

static inline void _sjs_copy(char *dest, char *start, char *end)
{
    for (; start <= end; ++start, ++dest)
        *dest = *start;
}

SVector *sjs_arr_loadFile(char *file)
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
    return sjs_arr_parseString((char *)&buff);
}

SVector *sjs_arr_parseString(char *str)
{
    // printf("%s\n", str);
    SVector *vect = svect_create();
    str = _sjs_arr_getopen(str);
    // printf("%s\n", str);
    for (; *str != ']' && *str != 0; ++str)
        if (*str != ' ' && *str != '\n' && *str != ',')
            str = _sjs_arr_getitem(str, vect);
    return vect;
}

void sjs_arr_setValue(SVector *array, unsigned int index, JsonValueType value)
{
    if(index > array->size)
        return;
    switch (value.type)
    {
    case _SJS_STRING:
    {
        if (value.value._string == null)
        {
            char *value_str = (char *)malloc(7);
            _sjs_copy(value_str + 1, (char*)"null", ((char*)"null") + 3);
            *(value_str + 5) = '\00';
            *value_str = _SJS_NULL;
            svect_set(array, index, value_str);
            break;
        }
        sstr_createeOnStack(value_str);
        sstr_appendc(value_str, _SJS_STRING);
        sstr_appendcs(value_str, value.value._string);
        sstr_serialize(value_str);
        svect_set(array, index, value_str->s_str);
        break;
    }
    case _SJS_EXTENDED_INT:
    {
        char *value_str = (char *)malloc(MAX_LENGTH_INT + 2);
        *value_str = _SJS_NUM;
        *(value_str + convert_IntToCStr(value.value._int, value_str + 1) + 1) = '\00';
        svect_set(array, index, value_str);
        break;
    }
    case _SJS_EXTENDED_LONG:
    {
        char *value_str = (char *)malloc(MAX_LENGTH_LONG + 2);
        *value_str = _SJS_NUM;
        *(value_str + convert_LongToCStr(value.value._long, value_str + 1) + 1) = '\00';
        svect_set(array, index, value_str);
        break;
    }
    case _SJS_EXTENDED_DOUBLE:
    {
        char *value_str = (char *)malloc(MAX_LENGTH_FLOAT + 2);
        *value_str = _SJS_NUM;
        *(value_str + convert_DoubleToCStr(value.value._double, value_str + 1) + 1) = '\00';
        svect_set(array, index, value_str);
        break;
    }
    case _SJS_BOOL:
    {
        char *value_str;
        if (value.value._bool == 0)
        {
            value_str = (char *)malloc(7);
            _sjs_copy(value_str + 1, (char*)"false", ((char*)"false") + 4);
            *(value_str + 6) = '\00';
        }
        else
        {
            value_str = (char *)malloc(7);
            _sjs_copy(value_str + 1, (char*)"true", ((char*)"true") + 3);
            *(value_str + 5) = '\00';
        }
        *value_str = _SJS_BOOL;
        svect_set(array, index, value_str);
        break;
    }
    case _SJS_JSON:
    {
        svect_set(array, index, sjs_toCString(value.value._jsonData));
        break;
    }
    case _SJS_ARRAY:
    {
        svect_set(array, index, sjs_arr_toCString(value.value._jsonArray));
        break;
    }
    }
}

void sjs_arr_appendValue(SVector *array, JsonValueType value)
{
    switch (value.type)
    {
    case _SJS_STRING:
    {
        if (value.value._string == null)
        {
            char *value_str = (char *)malloc(7);
            _sjs_copy(value_str + 1, (char*)"null", ((char*)"null") + 3);
            *(value_str + 5) = '\00';
            *value_str = _SJS_NULL;
            svect_insertNoCopy(array, value_str);
            break;
        }
        sstr_createeOnStack(value_str);
        sstr_appendc(value_str, _SJS_STRING);
        sstr_appendcs(value_str, value.value._string);
        sstr_serialize(value_str);
        svect_insertNoCopy(array, value_str->s_str);
        break;
    }
    case _SJS_EXTENDED_INT:
    {
        char *value_str = (char *)malloc(MAX_LENGTH_INT + 2);
        *value_str = _SJS_NUM;
        *(value_str + convert_IntToCStr(value.value._int, value_str + 1) + 1) = '\00';
        svect_insertNoCopy(array, value_str);
        break;
    }
    case _SJS_EXTENDED_LONG:
    {
        char *value_str = (char *)malloc(MAX_LENGTH_LONG + 2);
        *value_str = _SJS_NUM;
        *(value_str + convert_LongToCStr(value.value._long, value_str + 1) + 1) = '\00';
        svect_insertNoCopy(array, value_str);
        break;
    }
    case _SJS_EXTENDED_DOUBLE:
    {
        char *value_str = (char *)malloc(MAX_LENGTH_FLOAT + 2);
        *value_str = _SJS_NUM;
        *(value_str + convert_DoubleToCStr(value.value._double, value_str + 1) + 1) = '\00';
        svect_insertNoCopy(array, value_str);
        break;
    }
    case _SJS_BOOL:
    {
        char *value_str;
        if (value.value._bool == 0)
        {
            value_str = (char *)malloc(7);
            _sjs_copy(value_str + 1, (char*)"false", ((char*)"false") + 4);
            *(value_str + 6) = '\00';
        }
        else
        {
            value_str = (char *)malloc(7);
            _sjs_copy(value_str + 1, (char*)"true", ((char*)"true") + 3);
            *(value_str + 5) = '\00';
        }
        *value_str = _SJS_BOOL;
        svect_insertNoCopy(array, value_str);
        break;
    }
    case _SJS_JSON:
    {
        svect_insertNoCopy(array, sjs_toCString(value.value._jsonData));
        break;
    }
    }
}

static inline char *_sjs_arr_getitem(char *p, SVector *vect)
{
    char *_start;
    char *_end;
    int type = 0;
    int c = 1;
    /* switch through different possibilities */
    switch (*p)
    {
        /* strings with value true */
        char *val;
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
        val = (char*)"null";
        _start = val;
        _end = val + 3;
        p = p + 4;
        break;
    /* booleans with value false */
    case 'f':
        type = _SJS_BOOL;
        val = (char*)"false";
        _start = val;
        _end = val + 4;
        p = p + 5;
        break;
    /* booleans with value true */
    case 't':
        type = _SJS_BOOL;
        val = (char*)"true";
        _start = val;
        _end = val + 3;
        p = p + 4;
        break;
    /* json as key */
    case '{':
        type = _SJS_JSON;
        _start = p;
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
    /* numbers */
    default:
        if (*p <= '0' || *p >= '9') /* nan */
        {
            type = _SJS_NULL;
            _start = (char*)"NaN";
            _end = _start + 2;
            p = (char*)"\00";
            break;
        }
        type = _SJS_NUM;
        _start = p;
        for (; *p >= '0' && *p <= '9'; ++p)
            if (*p == 0)
                return p;
        _end = p - 1;
        break;
    }
    /* create value */
    int size = _end - _start;
    char *value = (char *)malloc((size) + 3 /* +2 to add type and \00 footer */);
    /* set value type */
    *value = type;
    _sjs_copy(value + 1, _start, _end);
    *(value + size + 2) = null;

    svect_insertNoCopy(vect, value);

    return p;
}

/* get functions */
JsonValue sjs_arr_getValue(SVector *arr, unsigned int index)
{
    char *result = svect_get(arr, index);
    JsonValue value;
    if (result == null)
    {
        value._string = null;
        return value;
    }
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
    case _SJS_BOOL:
        value._bool = strcmp(result, (char*)"true") == 0;
        return value;
    default:
        value._string = null;
        return value;
    }
}

JsonValueType sjs_arr_getValueAndType(SVector *arr, unsigned int index)
{
    char *result = svect_get(arr, index);
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
    case _SJS_BOOL:
        type.value._bool = strcmp(result, (char*)"true") == 0;
        type.type = _SJS_BOOL;
        return type;
    default:
        type.value._string = null;
        type.type = _SJS_NULL;
        return type;
    }
}

void sjs_arr_save(SVector *array, char *file)
{
    FILE *f = fopen(file, (char*)"w");
    if (f == null)
    {
        perror("open");
        exit(1);
    }
    SString *json_data = sjs_arr_toString(array);
    write(f->_fileno, json_data->s_str, json_data->s_size);
    if (ftruncate(f->_fileno, json_data->s_size) == 1)
    {
        perror("ftruncate");
        exit(1);
    }
    sstr_delete(json_data);
    fclose(f);
}

SString *sjs_arr_toString(SVector *arr)
{
    SString* str = sstr_creates((char*)"[",1);
    for (unsigned int i = 0; i < arr->size; ++i)
    {
        char *val = svect_get(arr, i);
        if (*val == _SJS_STRING)
        {
            sstr_appendc(str, '\"');
            sstr_appendcs(str, val + 1);
            sstr_appendc(str, '\"');
        }
        else
            sstr_appendcs(str, val + 1);
        if (i < (arr->size - 1))
            sstr_appendcs(str, (char*)",");
        free(val);
    }
    sstr_appendc(str, ']');
    free(arr->vect);
    free(arr);
    return str;
}

char *sjs_arr_toCString(SVector *arr)
{
    char c[2] = {_SJS_ARRAY, '['};
    sstr_createsOnStack(str, (char*)&c, 2);

    for (unsigned int i = 0; i < arr->size; ++i)
    {
        char *val = svect_get(arr, i);
        if (*val == _SJS_STRING)
        {
            sstr_appendc(str, '\"');
            sstr_appendcs(str, val + 1);
            sstr_appendc(str, '\"');
        }
        else
            sstr_appendcs(str, val + 1);
        if (i < (arr->size - 1))
            sstr_appendcs(str, (char *)",");
        free(val);
    }
    sstr_appendc(str, ']');
    free(arr->vect);
    free(arr);
    return str->s_str;
}

void sjs_arr_appendElement(char *file, char *element, unsigned int size)
{
    int fd = open(file, O_RDWR);
    if (fd == 0)
    {
        perror("open");
        exit(-1);
    }
    struct stat info;
    if (fstat(fd, &info) != 0)
    {
        perror("fstat");
        exit(-1);
    }
    int pos = info.st_size;
    find_pos:
    if (pos > 10)
    {
        char buff[11];
        lseek(fd, pos-10, SEEK_SET);
        read(fd, &buff, 10);
        buff[10] = '\00';
        for (char *_buff = ((char*)&buff) + 11; *_buff != ']'; _buff--, pos--)
            if (_buff == (char*)&buff)
                goto find_pos;
        lseek(fd, pos, SEEK_SET);
        convert_dprintf(fd, (char*)"\n  ,%x\n]", element, size);
    }
    else
    {
        char buff[info.st_size + 1];
        lseek(fd, 0, SEEK_SET);
        read(fd, &buff, info.st_size);
        buff[info.st_size] = '\00';
        for (char *_buff = ((char*)&buff) + info.st_size; *_buff != ']'; _buff--, pos--)
            if (_buff == (char *)&buff)
                return;
        lseek(fd, pos, SEEK_SET);
        convert_dprintf(fd, (char*)"  %x\n]", element, size);
    }
    close(fd);
}