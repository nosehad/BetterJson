#ifndef JSON_VALUE
    #define JSON_VALUE

    #include "../Storage/SQTree.h"
    #include "../Storage/SVector.h"

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
    
#endif