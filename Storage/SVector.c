#include "SVector.h"

SVector* svect_create()
{
    SVector* vector = (SVector*) malloc(sizeof(SVector));
    vector->capacity = sizeof(char*)*16;
    vector->vect = (char**) malloc(vector->capacity);
    vector->size = 0;
}

void svect_insert(SVector* vector, char* value)
{
    sstr_createeOnStack(value_string);
    sstr_appendcs(value_string, value);
    *(vector->vect+vector->size) = sstr_serialize(value_string);
    if(vector->size++ <= vector->size)
    {
        vector->capacity*=2;
        vector->vect = (char**) realloc(vector->vect, vector->capacity);
    }

}

void svect_insertNoCopy(SVector *vector, char *value)
{
    *(vector->vect + vector->size) = value;
    if (vector->size++ <= vector->size)
    {
        vector->capacity *= 2;
        vector->vect = (char **)realloc(vector->vect, vector->capacity);
    }
}

EXTERN_I void svect_remove(SVector *vector, unsigned int index)
{
    /* free old element */
    free(*(vector->vect + index));
    /* movup array */
    memmove(vector->vect + index, vector->vect + index + 1, (vector->size - index - 1) * sizeof(*vector->vect));
    vector->size--;
}

EXTERN_I char *svect_pop(SVector *vector, unsigned int index)
{
    char *ret = *(vector->vect + index);
    /* movup array */
    memmove(vector->vect + index, vector->vect + index + 1, (vector->size - index - 1) * sizeof(*vector->vect));
    vector->size--;
    return ret;
}

EXTERN_I char* svect_popl(SVector *vector)
{
    char* ret = null;
    if (vector->size > 0)
    {
        ret = *(vector->vect + vector->size - 1);
        /* decrement size */
        vector->size--;
    }
    return ret;
}

EXTERN_I void svect_set(SVector* vector, unsigned int i, char* value)
{
    *(vector->vect+i) = value;
}

EXTERN_I char* svect_get(SVector* vector, unsigned int index)
{
    return *(vector->vect+index);
}

void svect_delete(SVector*vector)
{
    char **start = vector->vect;
    char **end = vector->vect + vector->size;
    for (; start != end; ++start)
        free(*start);
    free(vector->vect);
    free(vector);
}