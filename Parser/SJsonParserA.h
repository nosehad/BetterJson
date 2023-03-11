/* json parser for arrays */
#ifndef SJPARSER_ARR_H
    #define SJPARSER_ARR_H
    #ifdef __cplusplus
        extern "C" {
    #endif

    #include <stdio.h>

    #include "../Storage/SVector.h"
    #include "../Utils/SString.h"
    #include "SJsonParser.h"

    SVector* sjs_arr_parseString(char*str);

    static inline char* _sjs_arr_getitem(char*p, SVector* vect);

    static inline char* _sjs_arr_getopen(char*str);

    SString* sjs_arr_toString(SVector*arr, int init_padding);

    void sjs_arr_delete(SVector* arr);

    #ifdef __cplusplus
        }
    #endif
#endif