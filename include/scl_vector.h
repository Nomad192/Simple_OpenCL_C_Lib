#ifndef SIMPLE_OPENCL_C_LIB__SCL_VECTOR_H
#define SIMPLE_OPENCL_C_LIB__SCL_VECTOR_H

#include "scl_types.h"
#include <stdlib.h>

typedef struct VECTOR_STRUCT {
    size_t type_size;
    size_t real_size;
    size_t size;
    void *data;
} VECTOR;

VECTOR *vec_create(size_t type_size, size_t init_size);

scl_status vec_check_size(VECTOR *vector);
scl_status vec_realloc(VECTOR *vector, size_t new_size);
scl_status vec_cut(VECTOR *vector);
scl_status vec_add(VECTOR *vector, void *elements, size_t number);

void *vector_get(VECTOR *vector, size_t i);
void *vec_unlink(VECTOR *vector);
void vec_free(VECTOR *vector);

#endif //SIMPLE_OPENCL_C_LIB__SCL_VECTOR_H
