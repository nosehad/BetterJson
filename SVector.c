#include "SVector.h"

SVector* svect_create()
{
    SVector* vector = (SVector*) malloc(sizeof(SVector));
    vector->capacity = sizeof(char*)*16;
    vector->size = 0;
}

void svect_insert(SVector* vector, char* value)
{
    *(vector->vect+vector->size) = value;
    if(vector->size++ <= vector->size)
    {
        vector->capacity*=2;
        vector->vect = (char**) realloc(vector->vect, vector->capacity);
    }

}

extern inline char* svect_get(SVector* vector, unsigned int index)
{
    return *(vector->vect+index);
}

void svect_delete(SVector*vector)
{
    free(vector->vect);
    free(vector);
}