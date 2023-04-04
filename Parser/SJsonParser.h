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

    /* is also used in array parser*/
    SQTree *sjs_loadFile(char *file);
    void sjs_insertPair(SQTree* json, char* key, JsonValueType value);
    void sjs_closeFile(void);
    EXTERN_I void _sjs_copy(char *dest, char *start, char *end);
    SQTree *sjs_parseString(char *str);
    EXTERN_I JsonValue sjs_getValue(SQTree *json, char *key);
    EXTERN_I JsonValueType sjs_getValueAndType(SQTree *json, char *key);
    SString *_sjs_toString(SQTree *json, int padding);
    char *_sjs_toCString(SQTree *json, int padding);
    int sjs_appendElement(char *file, char *element, unsigned int size);

    #define sjs_delete(json) sqtr_free(json)

    #define sjs_toCString(json) _sjs_toCString(json, 2)
    #define sjs_toString(json) _sjs_toString(json, 2)

    #ifdef __cplusplus
        }
    #endif
#endif