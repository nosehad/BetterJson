/* json parser for arrays */
#ifndef SJPARSER_ARR_H
    #define SJPARSER_ARR_H
    #ifdef __cplusplus
        extern "C" {
    #endif

    #include <stdio.h>

    #include "SVector.h"

    enum _sjs_datatypes
    {
        _SJS_JSON = 1,
        _SJS_ARRAY = 2,
        _SJS_NUM = 3,
        _SJS_NULL = 4,
        _SJS_STRING = 5,
        _SJS_BOOL = 6
    };

    SVector* sjs_arr_parseString(char*str);

    SString*_sjs_arr_toString(SVector*arr, int init_padding);

    #define sjs_toString(json) _sjs_toString(json, 2)

    #ifdef __cplusplus
        }
    #endif
#endif