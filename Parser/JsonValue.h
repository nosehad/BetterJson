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
        _SJS_BOOL = 6,
        _SJS_EXTENDED_INT = 7,
        _SJS_EXTENDED_LONG = 8,
        _SJS_EXTENDED_DOUBLE = 9
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

    extern inline JsonValueType sjs_createValueDouble(double value);
    extern inline JsonValueType sjs_createValueString(char* value);
    extern inline JsonValueType sjs_createValueInt(int value);
    extern inline JsonValueType sjs_createValueLong(long long value);
    extern inline JsonValueType sjs_createValueBool(char value);
    extern inline JsonValueType sjs_createValueJson(SQTree* value);
    extern inline JsonValueType sjs_createValueArray(SVector* value);

#endif