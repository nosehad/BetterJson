/* json parser for arrays */
#ifndef SJPARSER_ARR_H
#define SJPARSER_ARR_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "JsonValue.h"

    typedef struct SVector SVector;
    typedef struct SQTree SQTree;
    typedef struct SString SString;

#define sjs_arr_delete(arr) svect_delete(arr)
#define sjs_arr_createEmptyData() svect_create()

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"

    SQTree *sjs_arr_loadFile(char *file);
    SVector *sjs_arr_parseString(char *str);
    void sjs_arr_setValue(SVector *array, unsigned int index, JsonValueType value);
    void sjs_arr_appendValue(SVector *array, JsonValueType value);
    static inline char *_sjs_arr_getitem(char *p, SVector *vect);
    static inline char *_sjs_arr_getopen(char *str);
    extern inline JsonValue sjs_arr_getValue(SVector *arr, unsigned int index);
    extern inline JsonValueType sjs_arr_getValueAndType(SVector *arr, unsigned int index);
    SString *sjs_arr_toString(SVector *arr);
    char *sjs_arr_toCString(SVector *arr);
    int sjs_arr_appendElement(char *file, char *element, unsigned int size);

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
#endif