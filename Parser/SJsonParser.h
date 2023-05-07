#ifndef SJPARSER_H
#define SJPARSER_H
#ifdef __cplusplus
extern "C"
{
    #endif

    #include <stdio.h>

    #include "JsonValue.h"
    #include "SJsonParserA.h"
    #include "../Utils/Convert.h"
    #include "../Storage/SQTree.h"

    typedef SQTree JsonData;

    #define sjs_createEmptyData() sqtr_create()

    /* is also used in array parser*/
    SQTree *sjs_loadFile(char *file);
    void sjs_save(SQTree* json, char* file);
    void sjs_setPair(SQTree *json, char *key, JsonValueType value);;
    SQTree *sjs_parseString(char *str);
    JsonValue sjs_getValue(SQTree *json, char *key);
    JsonValueType sjs_getValueAndType(SQTree *json, char *key);
    SString *sjs_toString(SQTree *json);
    char *sjs_toCString(SQTree *json);
    void sjs_appendElement(char *file, char *element, unsigned int size);

    #define sjs_delete(json) sqtr_free(json)

    #ifdef __cplusplus
        }
    #endif
#endif