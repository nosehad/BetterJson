/* json parser for arrays */
#ifndef SJPARSER_ARR_H
    #define SJPARSER_ARR_H
    #ifdef __cplusplus
        extern "C" {
    #endif

    #include <stdio.h>

    #include "SVector.h"
    #include "SString.h"
    #include "SJsonParser.h"

    SVector* sjs_arr_parseString(char*str);

    static inline char* _sjs_arr_getitem(char*p, SVector* vect);

    static inline char* _sjs_arr_getopen(char*str);

    SString* sjs_arr_toString(SVector*arr, int init_padding);

    #ifdef __cplusplus
        }
    #endif
#endif