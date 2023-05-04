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

    #define sjs_createEmptyData() sqtr_create()

    /* is also used in array parser*/
    SQTree *sjs_loadFile(char *file);
    void sjs_save(SQTree* json, char* file);
    void sjs_setPair(SQTree *json, char *key, JsonValueType value);
    extern inline void _sjs_copy(char *dest, char *start, char *end);
    SQTree *sjs_parseString(char *str);
    extern inline JsonValue sjs_getValue(SQTree *json, char *key);
    extern inline JsonValueType sjs_getValueAndType(SQTree *json, char *key);
    SString *sjs_toString(SQTree *json);
    char *sjs_toCString(SQTree *json);
    int sjs_appendElement(char *file, char *element, unsigned int size);

    #define sjs_delete(json) sqtr_free(json)

    #ifdef __cplusplus
        }
    #endif
#endif