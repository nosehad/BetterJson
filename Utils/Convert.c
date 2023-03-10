#include "Convert.h"

/* macro that extends temporary string */
#define extend_string(p, val)  \
{                              \
    *p = val;                  \
    ++p;                       \
}  

/* return type by numberType */
int convert_getType(char* cstr)
{
    int type = NT_INT;
    if(*cstr == '-')
        ++cstr;
    int i;
    for(i = 0;*cstr != null;++i, ++cstr)
    {
        switch(*cstr)
        {
            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7':
            case '8': case '9':
                continue;
            case '.':
                return NT_FLOAT;
            default:
                return  NT_NONE;
        }
    }
    if(type == NT_INT && i > MAX_LENGTH_UINT)
        return NT_LONG;
    return NT_INT;
}                 

int convert_LongToCStr(long long l, char* dest)
{
    char*b = (char*)__builtin_alloca(MAX_LENGTH_INT);
    char*a = b;
    char n;

    /* check for special cases */
    if(l < 0) /* number negative */
    {
        n = 1;
        l *= -1; /* make number positive */
    }
    else if(l == 0) /* number is 0 */
    {
        *dest = '0';
        return 1;
    }

    for(;l != 0; l /= 10)
        extend_string(b , l % 10 + '0');

    if(n)
        extend_string(b, '-')

    int size = b-a;
    /* reverse copy converted int to final string */
    for(--b;b >= a; --b, dest++)
        *dest = *b;

    return size;
}

int convert_ULongToCStr(unsigned long long l, char* dest)
{
    char*b = (char*)__builtin_alloca(MAX_LENGTH_UINT);
    char*a = b;

    if(l == 0)
    {
        *dest = '0';
        return 1;
    }

    for(;l != 0; l /= 10)
        extend_string(b , l % 10 + '0');

    int size = b-a;
    /* reverse copy converted int to final string */
    for(--b;b >= a; --b, dest++)
        *dest = *b;

    return size;
}

int convert_IntToCStr(int i, char* dest)
{
    char*b = (char*)__builtin_alloca(MAX_LENGTH_INT);
    char*a = b;
    char n = 0;

    /* check for special cases */
    if(i < 0) /* number negative */
    {
        n = 1;
        i *= -1; /* make number positive */
    }
    else if(i == 0) /* number is 0 */
    {
        *dest = '0';
        return 1;
    }

    for(;i != 0; i /= 10)
        extend_string(b , i % 10 + '0');

    if(n)
        extend_string(b, '-')

    int size = b-a;
    /* reverse copy converted int to final string */
    for(--b;b >= a; --b, dest++)
        *dest = *b;

    return size;
}

int convert_UIntToCStr(unsigned int i, char* dest)
{
    char*b = (char*)__builtin_alloca(MAX_LENGTH_UINT);
    char*a = b;

    if(i == 0)
    {
        *dest = '0';
        return 1;
    }

    for(;i != 0; i /= 10)
        extend_string(b , i % 10 + '0');

    int size = b-a;
    /* reverse copy converted int to final string */
    for(--b;b >= a; --b, dest++)
        *dest = *b;

    return size;
}

unsigned int convert_CStrToUInt(char* cstr)
{
    unsigned int i = 0;
    for(;*cstr != '\0'; ++cstr)
        i = i * 10 + *cstr - '0';
    return i;
}

int convert_CStrToInt(char* cstr)
{
    char n;
    if(*cstr == '-') /* check if number should be negative */
    {
        cstr++;
        n = 1;
    } else n = 0;
    int i = 0;
    for(;*cstr != '\0'; ++cstr)
        i = i * 10 + *cstr - '0';
    if(n)
        return i*(-1); /* make negative */
    return i;
}

unsigned long long convert_CStrToULong(char* cstr)
{
    unsigned long long i = 0;
    for(;*cstr != '\0'; ++cstr)
        i = i * 10 + *cstr - '0';
    return i;
}

long long convert_CStrToLong(char* cstr)
{
    char n = 0;
    if(*cstr == '-') /* check if number should be negative */
    {
        cstr++;
        n = 1;
    } else n = 0;
    long long i = 0;
    for(;*cstr != '\0'; ++cstr)
        i = i * 10 + *cstr - '0';
    if(n)
        return i*(-1); /* make negative */
    return i;
}

float convert_CStrToFloat(char* cstr)
{
    /* check if number is negative */
    char n = 0;
    if(*cstr == '-')
    {
        cstr++;
        n = 1;
    } else n = 0;

    /* parse integer before point */
    float f = 0;
    for(;*cstr != '.'; ++cstr)
    {
        if(*cstr == '\0')
            if(n)
                return f * -1 /* make number negative */;
            else 
                return f;
        f = f * 10 + *cstr - '0';
    }

    /* parse integer after point */
    float a, b;
    for(cstr++, a = 1, b = 0;*cstr != '\0'; ++cstr)
    {
        a *= 10;
        b = b * 10 + *cstr - '0';
    }
    if(n)
        return (f/* integer before point */ + (b/a)/* integer after point */) * -1 /* make negative */;
    return f/* integer before point */ + (b/a)/* integer after point */;
}

double convert_CStrToDouble(char* cstr)
{
    /* check if number is negative */
    char n = 0;
    if(*cstr == '-')
    {
        cstr++;
        n = 1;
    } else n = 0;

    /* parse integer before point */
    double d = 0;
    for(;*cstr != '.'; ++cstr)
    {
        if(*cstr == '\0')
            if(n)
                return d * -1 /* make number negative */;
            else 
                return d;
        d = d * 10 + *cstr - '0';
    }

    /* parse integer after point */
    double a, b;
    for(cstr++, a = 1, b = 0;*cstr != '\0'; ++cstr)
    {
        a *= 10;
        b = b * 10 + *cstr - '0';
    }
    if(n)
        return (d/* integer before point */ + (b/a)/* integer after point */) * -1 /* make negative */;
    return d/* integer before point */ + (b/a)/* integer after point */;
}

int convert_FloatToCStr(float f, char* dest)
{
    unsigned long long significant, fractional;
    char n = 0;

    char*a; 
    char*b = (char*)__builtin_alloca(MAX_LENGTH_FLOAT);
    a = b;
    if(f < 0.0F)
    {
        n = 1;
        f *= -1; /* make float positive */
        if(f > (float)(unsigned long long)-1)
        {
            strcpy(dest, "-infinity");
            return 9;
        }
    }
    if(f > (float)(unsigned long long)-1)
    {
        strcpy(dest, "infinity");
        return 8;
    }

    /* determine significant and fractional */
    significant = (unsigned long long) f;
    f -= significant;
    f *= FLOAT_CONVERSION_CONSTANT;
    fractional = (unsigned long long) f;

    /* convert fractional to string */
    if(fractional == 0)
        extend_string(b, '0')
    else
        for(;fractional != 0; fractional /= 10)
            extend_string(b, fractional % 10 + '0');

    extend_string(b, '.');

    /* convert significant to string */
    if(significant == 0)
        extend_string(b, '0')
    else
        for(;significant != 0; significant /= 10)
            extend_string(b, significant % 10 + '0');

    if(n)
        extend_string(b, '-');

    int size = b-a;
    /* reverse copy converted float to final string */
    for(--b;b >= a; --b, dest++)
        *dest = *b;
    return size;
}

int convert_DoubleToCStr(double d, char* dest)
{
    unsigned long long significant, fractional;
    char n = 0;

    char*a; 
    char*b = (char*)__builtin_alloca(MAX_LENGTH_FLOAT);
    a = b;
    if(d < 0.0F)
    {
        n = 1;
        d *= -1; /* make double positive */
        if(d > (double)(unsigned long long)-1)
        {
            strcpy(dest, "-infinity");
            return 9;
        }
    }
    if(d > (double)(unsigned long long)-1)
    {
        strcpy(dest, "infinity");
        return 8;
    }

    /* determine significant and fractional */
    significant = (unsigned long long) d;
    d -= significant;
    d *= DOUBLE_CONVERSION_CONSTANT;
    fractional = (unsigned long long) d;

    /* convert fractional to string */
    if(fractional == 0)
        extend_string(b, '0')
    else
        for(;fractional != 0; fractional /= 10)
            extend_string(b, fractional % 10 + '0');

    extend_string(b, '.');

    /* convert significant to string */
    if(significant == 0)
        extend_string(b, '0')
    else
        for(;significant != 0; significant /= 10)
            extend_string(b, significant % 10 + '0');

    if(n)
        extend_string(b, '-');

    int size = b-a;/* macro that extends temporary string of dynamic length */

    /* reverse copy converted float to final string */
    for(--b;b >= a; --b, dest++)
        *dest = *b;
    return size;
}

#undef FLOAT_CONVERSION_CONSTANT
#undef DOUBLE_CONVERSION_CONSTANT