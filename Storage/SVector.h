/* json parser for arrays */
#ifndef SVECTOR_H
    #define SVECTOR_H
    #ifdef __cplusplus
        extern "C" {
    #endif

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include "../Utils/null.h"
    #include "../Utils/SString.h"

    typedef struct _SVector SVector;

    struct _SVector
    {
        char**vect;
        unsigned int size;
        unsigned int capacity;
    };

    SVector* svect_create();
    void svect_insert(SVector* vector, char* value);
    void svect_insertNoCopy(SVector *vector, char *value);
    extern void svect_remove(SVector *vector, unsigned int index);
    extern char *svect_pop(SVector *vector, unsigned int index);
    extern char *svect_popl(SVector *vector);
    extern void svect_set(SVector *vector, unsigned int i, char *value);
    extern char *svect_get(SVector *vector, unsigned int index);
    void svect_delete(SVector *vector);

    #ifdef __cplusplus
        }
    #endif
#endif