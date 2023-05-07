/* json parser for arrays */
#ifndef SJPARSER_ARR_H
    #define SJPARSER_ARR_H
    #ifdef __cplusplus
        extern "C" {
    #endif
    #include "SJsonParser.h"
    #include "JsonValue.h"
    #include "SString.h"

    struct SQTree;
    struct SVector;

    typedef struct SVector JsonArrayData;

    void svect_delete(struct SVector *vector);
    #define sjs_arr_delete(arr) svect_delete(arr)
    struct SVector *svect_create();
    #define sjs_arr_createEmptyData() svect_create()

    struct SVector *sjs_arr_loadFile(char *file);
    void sjs_arr_save(struct SVector *json, char *file);
    struct SVector *sjs_arr_parseString(char *str);
    void sjs_arr_setValue(struct SVector *array, unsigned int index, JsonValueType value);
    void sjs_arr_appendValue(struct SVector *array, JsonValueType value);
    static inline char *_sjs_arr_getitem(char *p, struct SVector *vect);
    static inline char *_sjs_arr_getopen(char *str);
    JsonValue sjs_arr_getValue(struct SVector *arr, unsigned int index);
    JsonValueType sjs_arr_getValueAndType(struct SVector *arr, unsigned int index);
    SString *sjs_arr_toString(struct SVector *arr);
    char *sjs_arr_toCString(struct SVector *arr);
    void sjs_arr_appendElement(char *file, char *element, unsigned int size);


#ifdef __cplusplus
        }
    #endif
#endif