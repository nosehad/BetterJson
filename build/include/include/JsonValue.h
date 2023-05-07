#ifndef JSON_VALUE
    #define JSON_VALUE

    struct SQTree;
    struct SVector;

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
        struct SQTree*_jsonData;
        struct SVector* _jsonArray;
    };

    typedef struct _sjs_jsonValueType JsonValueType;
    struct _sjs_jsonValueType
    {
        union _sjs_jsonValue value;
        int type;
    };

    extern JsonValueType sjs_createValueDouble(double value);
    extern JsonValueType sjs_createValueString(char *value);
    extern JsonValueType sjs_createValueInt(int value);
    extern JsonValueType sjs_createValueLong(long long value);
    extern JsonValueType sjs_createValueBool(char value);
    extern JsonValueType sjs_createValueArray(struct SVector *value);
    extern JsonValueType sjs_createValueJson(struct SQTree *value);

#endif