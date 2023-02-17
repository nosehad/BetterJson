#ifndef SJPARSER_H
    #define SJPARSER_H
    #ifdef __cplusplus
        extern "C" {
    #endif

    #include <stdio.h>

    #include "SQTree.h"

    enum _sjs_datatypes
    {
        _SJS_JSON = 1,
        _SJS_ARRAY = 2,
        _SJS_NUM = 3,
        _SJS_NULL = 4,
        _SJS_STRING = 5,
        _SJS_BOOL = 6
    };

    static inline char* _sjs_parseOpen(char*p);

    static inline char* _sjs_parsePair(char*p, SQTree*json);

    /* is also used in array parser*/
    extern inline void _sjs_copy(char*dest, char*start, char*end);

    static inline void _sjs_setKey(SString* str, char* key, char* val, int padding);

    SQTree* sjs_parseString(char*str);

    SString*_sjs_toString(SQTree*json, int padding);

    #define sjs_toString(json) _sjs_toString(json, 2)

    #ifdef __cplusplus
        }
    #endif
#endif