#ifndef SJPARSER_H
#define SJPARSER_H
#ifdef __cplusplus
extern "C"
{
    #endif

    #include <stdio.h>

    #include "JsonValue.h"
    #include "SJsonParserA.h"
    #include "../Utils/inline.h"
    #include "../Utils/Convert.h"
    #include "../Storage/SQTree.h"

    enum _sjs_datatypes
    {
        _SJS_JSON = 1,
        _SJS_ARRAY = 2,
        _SJS_NUM = 3,
        _SJS_NULL = 4,
        _SJS_STRING = 5,
        _SJS_BOOL = 6
    };

    /* is also used in array parser*/
    EXTERN_I void _sjs_copy(char *dest, char *start, char *end);
    SQTree *sjs_parseString(char *str);
    EXTERN_I JsonValue sjs_getValue(SQTree *json, char *key);
    EXTERN_I JsonValueType sjs_getValueAndType(SQTree *json, char *key);
    SString *_sjs_toString(SQTree *json, int padding);
    char *_sjs_toCString(SQTree *json, int padding);

    #define sjs_delete(json) sqtr_free(json)

    #define sjs_toCString(json) _sjs_toCString(json, 2)
    #define sjs_toString(json) _sjs_toString(json, 2)

#ifdef __cplusplus
        }
    #endif
#endif