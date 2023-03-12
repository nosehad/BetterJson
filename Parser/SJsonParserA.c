#include "SJsonParserA.h"

STATIC_I char* _sjs_arr_getopen(char*str)
{
    for(;*str != '[' && *str != 0; ++str);
    return str+1;
}

SVector* sjs_arr_parseString(char*str)
{
    //printf("%s\n", str);
    SVector* vect = svect_create();
    str = _sjs_arr_getopen(str);
            //printf("%s\n", str);
    for(;*str != ']' && *str != 0; ++str)
        if(*str != ' ' && *str != '\n' && *str != ',')
            str = _sjs_arr_getitem(str, vect);
    return vect;
}

STATIC_I char* _sjs_arr_getitem(char*p, SVector* vect)
{
    char* _start;
    char* _end;
    int type = 0;
    int c = 1;
    /* switch through different possibilities */
    switch (*p)
    {
        /* strings with value true */ 
        char*val;
        case '"':
            type = _SJS_STRING;
            ++p;
            _start = p;
            for(;*p != '"';++p)
            {
                if(*p == 0)
                    return p;
            }
            _end = p-1;
            break;
        /* null */
        case 'n':
            type = _SJS_NULL;
            val = "null"; 
            _start = val;
            _end = val + 3;
            p = p +4;
            break;
        /* booleans with value false */ 
        case 'f':
            type = _SJS_BOOL;
            val = "false"; 
            _start = val;
            _end = val + 4;
            p = p +5;
            break;
        /* booleans with value true */    
        case 't':
            type = _SJS_BOOL;
            val = "true"; 
            _start = val;
            _end = val + 3;
            p = p +4;
            break;
        /* json as key */
        case '{':
            type = _SJS_JSON;
            _start = p;
            for(++p;; ++p)
            {
                if(*p == 0)
                    return p;
                else if(*p == '{')
                    ++c;
                else if(*p == '}')
                {
                    --c;
                    if(c == 0)
                    {
                        _end = p;
                        break;
                    }
                }
            }
            break;
        /* numbers */
        default:
            if(*p <= '0' || *p >= '9') /* nan */
            {
                type = _SJS_NULL;
                _start = "NaN";
                _end = _start + 2;
                p = "\00";
                break; 
            }
            type = _SJS_NUM;
            _start = p;
            for(;*p >= '0' && *p <= '9';++p)
                if(*p == 0)
                    return p;
            _end = p-1;
            break;
    }
    /* create value */
    int size = _end-_start;
    char* value = (char*)malloc((size)+3 /* +2 to add type and \00 footer */);
    /* set value type */
    *value = type;
    _sjs_copy(value+1, _start, _end);
    *(value + size + 2) = null;

    svect_insert(vect, value);

    return p;
}

/* get functions */
EXTERN_I JsonValue sjs_arr_getValue(SVector*arr, unsigned int index)
{
    char* result = svect_get(arr, index);
    JsonValue value;
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
            value._bool = strcmp(result, "true") == 0;
            return value;
        default:
            value._string = null;
            return value;
    }
}

EXTERN_I JsonValueType sjs_arr_getValueAndType(SVector*arr, unsigned int index)
{
    char* result = svect_get(arr, index);
    JsonValueType type;
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
            type.value._bool = strcmp(result, "true") == 0;
            type.type = _SJS_BOOL;
            return type;
        default:
            type.value._string = null;
            type.type = _SJS_NULL;
            return type;
    }
}

SString* sjs_arr_toString(SVector*arr, int init_padding)
{
    SString* str = sstr_createcs("[\n");
    for(unsigned int i = 0; i < arr->size; ++i)
    {
        sstr_fill(str, ' ', init_padding);
        char* val = svect_get(arr, i);
        if(*val == _SJS_STRING)
        {
            sstr_appendc(str, '\"');
            sstr_appendcs(str, val+1);
            sstr_appendc(str, '\"');
        } else 
            sstr_appendcs(str, val+1);
        if(i == (arr->size -1))
            sstr_appendc(str, '\n');
        else
            sstr_appendcs(str, ",\n");
    }
    sstr_fill(str, ' ', init_padding-1);
    sstr_appendc(str, ']');
    return str;
}

void sjs_arr_delete(SVector* arr)
{
    char** start = arr->vect;
    char** end = arr->vect + arr->size;
    for(;start != end; ++start)
        free(*start);
    free(arr->vect);
    free(arr);
}