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
    #include "SJsonParser.h"
    #include "JsonValue.h"

    typedef SVector JsonArrayData;

    #define sjs_arr_delete(arr) svect_delete(arr)
    #define sjs_arr_createEmptyData() svect_create()

    SVector *sjs_arr_loadFile(char *file);
    void sjs_arr_save(SVector *json, char *file);
    SVector *sjs_arr_parseString(char *str);
    void sjs_arr_setValue(SVector *array, unsigned int index, JsonValueType value);
    void sjs_arr_appendValue(SVector *array, JsonValueType value);
    static inline char *_sjs_arr_getitem(char *p, SVector *vect);
    static inline char *_sjs_arr_getopen(char *str);
    JsonValue sjs_arr_getValue(SVector *arr, unsigned int index);
    JsonValueType sjs_arr_getValueAndType(SVector *arr, unsigned int index);
    SString *sjs_arr_toString(SVector *arr);
    char *sjs_arr_toCString(SVector *arr);
    void sjs_arr_appendElement(char *file, char *element, unsigned int size);


#ifdef __cplusplus
        }
    #endif
#endif