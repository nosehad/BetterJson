#ifndef CONVERT_H
    #define CONVERT_H
    #ifdef __cplusplus
        extern "C" {
    #endif
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/mman.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdarg.h>
    #include "SString.h"
    
    /* the amount of digits of original floating point that should be used in converted String */
    /* the amount of zeros representate the amount of digits that are put into the new string after converting the floating point*/
    #define FLOAT_CONVERSION_CONSTANT 100
    #define DOUBLE_CONVERSION_CONSTANT 10000
    
    /* max amount of characters in specific number type */
    #define MAX_LENGTH_BOOL 5
    #define MAX_LENGTH_INT 12
    #define MAX_LENGTH_LONG 21
    #define MAX_LENGTH_UINT 11
    #define MAX_LENGTH_ULONG 20
    #define MAX_LENGTH_FLOAT MAX_LENGTH_LONG/* significant */ +MAX_LENGTH_ULONG/* fractional */ +1 /*. symbol*/
                                            /* = 42 */
    
    enum numberType
    {
        NT_INT,
        NT_LONG,
        NT_FLOAT,
        NT_NONE
    };
    
    /* return type by numberType */
    int convert_getType(char* cstr);                                        
    int convert_LongToCStr(long long l, char* dest);
    int convert_ULongToCStr(unsigned long long l, char* dest);
    int convert_IntToCStr(int i, char* dest);
    int convert_UIntToCStr(unsigned int i, char* dest);
    unsigned int convert_CStrToUInt(char* cstr);
    int convert_CStrToInt(char* cstr);
    unsigned long long convert_CStrToULong(char* cstr);
    long long convert_CStrToLong(char* cstr);
    float convert_CStrToFloat(char* cstr);
    double convert_CStrToDouble(char* cstr);
    int convert_FloatToCStr(float f, char* dest);
    int convert_DoubleToCStr(double d, char* dest);
    #ifdef __cplusplus
        }
    #endif
#endif