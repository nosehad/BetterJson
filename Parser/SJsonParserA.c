#include "SJsonParserA.h"

SVector* sjs_arr_parseString(char*str)
{
    //printf("%s\n", str);
    SVector* vect = svect_create();
    str = _sjs_arr_getopen(str);
            //printf("%s\n", str);
    for(;*str != ']' && *str != 0; ++str)
    {
        str = _sjs_arr_getitem(str, vect);
    }
    return vect;
}

static inline char* _sjs_arr_getitem(char*p, SVector* vect)
{
    char* _start;
    char* _end;
    for(;*p == ' ' || *p == '\n' || *p == ',';++p);
    if(*p == 0)
        return p;
    int type = 0;
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
        /* numbers */
        default:
            type = _SJS_NUM;
            _start = p;
            for(;*p >= '0' && *p <= '9';++p)
                if(*p == 0)
                    return p;
            _end = p-1;
            break;
    }
    /* create value */
    char* value = (char*)malloc((_end-_start)+2 /* +2 to add type and \00 footer */);
    /* set value type */
    *value = type;
    _sjs_copy(value+1, _start, _end);

    svect_insert(vect, value);

    return p;
}

static inline char* _sjs_arr_getopen(char*str)
{
    for(;*str != '[' && *str != 0; ++str);
    return str +1;
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