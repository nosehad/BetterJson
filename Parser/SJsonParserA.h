/* json parser for arrays */
#ifndef SJPARSER_ARR_H
    #define SJPARSER_ARR_H
    #ifdef __cplusplus
        extern "C" {
    #endif

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "../Storage/SVector.h"
    #include "../Utils/Convert.h"
    #include "../Utils/SString.h"
    #include "../Utils/inline.h"
    #include "SJsonParser.h"
    #include "JsonValue.h"

    #define sjs_arr_delete(arr) svect_delete(arr)

    SQTree *sjs_arr_loadFile(char *file);
    SVector *sjs_arr_parseString(char *str);
    void sjs_arr_setValue(SVector *array, unsigned int index, JsonValueType value);
    void sjs_arr_appendValue(SVector *array, JsonValueType value);
    STATIC_I char *_sjs_arr_getitem(char *p, SVector *vect);
    STATIC_I char *_sjs_arr_getopen(char *str);
    EXTERN_I JsonValue sjs_arr_getValue(SVector *arr, unsigned int index);
    EXTERN_I JsonValueType sjs_arr_getValueAndType(SVector *arr, unsigned int index);
    SString *sjs_arr_toString(SVector *arr);
    char *sjs_arr_toCString(SVector *arr);
    int sjs_arr_appendElement(char *file, char *element, unsigned int size);


#ifdef __cplusplus
        }
    #endif
#endif