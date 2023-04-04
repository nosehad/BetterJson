#ifndef JSON_VALUE
    #define JSON_VALUE

    #include "../Storage/SQTree.h"
    #include "../Storage/SVector.h"

    enum _sjs_datatypes
    {
        _SJS_JSON = 1,
        _SJS_ARRAY = 2,
        _SJS_NUM = 3,
        _SJS_NULL = 4,
        _SJS_STRING = 5,
        _SJS_BOOL = 6
    };

    typedef union _sjs_jsonValue JsonValue;
    union _sjs_jsonValue
    {
        char _bool; 
        int _int;
        long long _long;
        double _double;
        char* _string;
        SQTree* _jsonData;
        SVector* _jsonArray;
    };

    typedef struct sjs_jsonValueType JsonValueType;
    struct sjs_jsonValueType
    {
        union _sjs_jsonValue value;
        int type;
    };

    struct sjs_jsonValueType sjs_createValueDouble(double value)
    {
        struct sjs_jsonValueType type;
        type.type = _SJS_NUM;
        type.value._double = value;
    }

    struct sjs_jsonValueType sjs_createValueString(char* value)
    {
        struct sjs_jsonValueType type;
        type.type = _SJS_NUM;
        type.value._string = value;
    }

    struct sjs_jsonValueType sjs_createValueInt(int value)
    {
        struct sjs_jsonValueType type;
        type.type = _SJS_NUM;
        type.value._int = value;
    }

    struct sjs_jsonValueType sjs_createValueLong(long long value)
    {
        struct sjs_jsonValueType type;
        type.type = _SJS_NUM;
        type.value._long = value;
    }

    struct sjs_jsonValueType sjs_createValueBool(char value)
    {
        struct sjs_jsonValueType type;
        type.type = _SJS_NUM;
        type.value._bool = value;
    }

#endif