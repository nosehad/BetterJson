/* json parser for arrays */
#ifndef SVECTOR_H
    #define SVECTOR_H
    #ifdef __cplusplus
        extern "C" {
    #endif

    #include <stdlib.h>
    #include <stdio.h>

    #include "../Utils/inline.h"

    typedef struct _SVector SVector;

    struct _SVector
    {
        char**vect;
        unsigned int size;
        unsigned int capacity;
    };

    SVector* svect_create();
    void svect_insert(SVector* vector, char* value);
    EXTERN_I void svect_set(SVector* vector, unsigned int i, char* value);
    EXTERN_I char* svect_get(SVector* vector, unsigned int index);
    void svect_delete(SVector*vector);
    #ifdef __cplusplus
        }
    #endif
#endif