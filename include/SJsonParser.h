#ifndef SJPARSER_H
#define SJPARSER_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "JsonValue.h"

typedef struct SQTree SQTree;
typedef struct SString SString;

#define sjs_createEmptyData() sqtr_create()
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"

/* is also used in array parser*/
SQTree *sjs_loadFile(char *file);
void sjs_save(SQTree *json, char *file);
void sjs_setPair(SQTree *json, char *key, JsonValueType value);
SQTree *sjs_parseString(char *str);
extern inline JsonValue sjs_getValue(SQTree *json, char *key);
extern inline JsonValueType sjs_getValueAndType(SQTree *json, char *key);
SString *sjs_toString(SQTree *json);
char *sjs_toCString(SQTree *json);
int sjs_appendElement(char *file, char *element, unsigned int size);
#pragma GCC diagnostic pop

#define sjs_delete(json) sqtr_free(json)

#ifdef __cplusplus
}
#endif
#endif