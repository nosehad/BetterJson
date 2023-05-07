#ifndef SJPARSER_H
#define SJPARSER_H
#ifdef __cplusplus
extern "C"
{
    #endif
    #include "JsonValue.h"
    #include "SJsonParserA.h"
    #include "SString.h"
    
    struct SQTree;

    typedef struct SQTree JsonData;

    struct SQTree *sqtr_create();
    #define sjs_createEmptyData() sqtr_create()

    /* is also used in array parser*/
    struct SQTree *sjs_loadFile(char *file);
    void sjs_save(struct SQTree* json, char* file);
    void sjs_setPair(struct SQTree *json, char *key, JsonValueType value);;
    struct SQTree *sjs_parseString(char *str);
    JsonValue sjs_getValue(struct SQTree *json, char *key);
    JsonValueType sjs_getValueAndType(struct SQTree *json, char *key);
    SString *sjs_toString(struct SQTree *json);
    char *sjs_toCString(struct SQTree *json);
    void sjs_appendElement(char *file, char *element, unsigned int size);

    #define sjs_delete(json) sqtr_free(json)

    #ifdef __cplusplus
        }
    #endif
#endif