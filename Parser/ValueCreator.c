#include "JsonValue.h"

inline JsonValueType sjs_createValueDouble(double value)
{
    JsonValueType type;
    type.type = _SJS_EXTENDED_DOUBLE;
    type.value._double = value;
    return type;
}

inline JsonValueType sjs_createValueString(char *value)
{
    JsonValueType type;
    type.type = _SJS_STRING;
    type.value._string = value;
    return type;
}

inline JsonValueType sjs_createValueInt(int value)
{
    JsonValueType type;
    type.type = _SJS_EXTENDED_INT;
    type.value._int = value;
    return type;
}

inline JsonValueType sjs_createValueLong(long long value)
{
    JsonValueType type;
    type.type = _SJS_EXTENDED_LONG;
    type.value._long = value;
    return type;
}

inline JsonValueType sjs_createValueBool(char value)
{
    JsonValueType type;
    type.type = _SJS_BOOL;
    type.value._bool = value;
    return type;
}

inline JsonValueType sjs_createValueArray(SVector* value)
{
    JsonValueType type;
    type.type = _SJS_ARRAY;
    type.value._jsonArray = value;
    return type;
}

inline JsonValueType sjs_createValueJson(SQTree *value)
{
    JsonValueType type;
    type.type = _SJS_JSON;
    type.value._jsonArray = value;
    return type;
}