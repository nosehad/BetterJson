#include "SJsonParser.h"

SQTree* sjs_parseString(char*str)
{
    SQTree*json = sqtr_create();
    str = _sjs_parseOpen(str);
    for(;*str != null; ++str)
    {
        str = _sjs_parsePair(str, json);
    }
    return json;
}

static inline char* _sjs_parseOpen(char*p)
{
    for(;*p != null; ++p)
    {
        if(*p == '{')
            return p;
    }
    return p;
}

static inline char* _sjs_parsePair(char*p, SQTree*json)
{
    for(;*p == ' ' || *p == ',' || *p == '"' || *p == '\n' || *p == '}' || *p == '{';++p)
        if(*p == 0)
            return p;
    
    /* get key */
    char*_start = p;
    for(;(*p) != '"'; p++)
        if(*p == 0)
            return p;
    char*_end = (p++)-1; 

    /* create key */
    char* key = (char*)malloc((_end-_start)+1);
    _sjs_copy(key, _start, _end);
    
    /* get value */
    for(;*p == ' ' || *p == ':'|| *p == '\n';++p); /* increment p until value starts*/
    int type = 0;
    /* switch through different possibilities */
    printf("%c\n", *p);
    int c;
    switch (*p)
    {
        /* json as key */
        case '{':
            type = _SJS_JSON;
            _start = p;
            c = 1;
            for(;; ++p)
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
            _end = p;
            break;
    }

    /* create value */
    char* value = (char*)malloc((_end-_start)+2 /* +2 to add type and \00 footer */);
    /* set value type */
    *value = type;
    _sjs_copy(value+1, _start, _end);

    /* insert value to tree */
    sqtr_set(json, key, value);
    /* increase p until row is over */
    for(;*p != ',' && *p != '}' && *p != 0; ++p);
    return p; /* return current state of p*/
}

extern inline void _sjs_copy(char*dest, char*start, char*end)
{
    for(;start <= end; ++start, ++dest)
    {
        *dest = *start;
    }
}

static inline void _sjs_setKey(SString* str, char* key, char* val, int padding)
{
    for(;padding>0;padding--)
        sstr_appendc(str, ' ');
    sstr_appendc(str, '\"');
    sstr_appendcs(str, key);
    sstr_appendcs(str, "\":");
    if(*val == _SJS_STRING)
    {
        sstr_appendc(str, '\"');
        sstr_appendcs(str, val+1);
        sstr_appendc(str, '\"');
    } else 
        sstr_appendcs(str, val+1);
}

SString*_sjs_toString(SQTree*json, int padding)
{
    SString*ret = sstr_createe();
    if(sqtr_empty(json) == 1)
    {
        sstr_appendcs(ret, "{}");
        return ret;
    }
    sstr_appendcs(ret, "{\n");
    for(SQNode* current = sqtr_popl(json);;)
    {
        if(sqtr_empty(json))
        {
            _sjs_setKey(ret, current->key, current->value, padding);
            sstr_appendc(ret, '\n');
            break;
        }
        else
        {
            _sjs_setKey(ret, current->key, current->value, padding);
            sstr_appendcs(ret, ",\n");
        }
        current = sqtr_popl(json);
    }
    sstr_appendcs(ret, "}");
}

void sjs_delete(SQTree* json)
{
    for(SQNode* node;!sqtr_empty(json);node = sqtr_popl(json))
    {
        free(node->key);
        free(node->value);
    }
    free(json);
}