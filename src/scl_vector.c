#include "scl_vector.h"

#include "scl_tools.h"

VECTOR *vec_create(size_t type_size, size_t init_size) {
    VECTOR *vector = (VECTOR *) malloc(sizeof(VECTOR));
    if (vector != NULL) {
        vector->type_size = type_size;
        vector->real_size = init_size;
        vector->size = 0;
        vector->data = malloc(type_size * init_size);

        if (vector->data == NULL) {
            free(vector);
            vector = NULL;
        }
    }

    return vector;
}

scl_status vec_check_size(VECTOR *vector) {
    if (vector->size >= vector->real_size) {
        return vec_realloc(vector, vector->real_size * 2);
    }
    return SCL_SUCCESS;
}

scl_status vec_realloc(VECTOR *vector, size_t new_size) {
    vector->real_size = new_size;
    void *new_data = realloc(vector->data, vector->real_size * vector->type_size);
    if (new_data == NULL) {
        return SCL_OUT_OF_MEMORY;
    }
    vector->data = new_data;
    return SCL_SUCCESS;
}

scl_status vec_cut(VECTOR *vector) {
    return vec_realloc(vector, vector->size);
}

scl_status vec_add(VECTOR *vector, void *elements, size_t number) {
    vector->size += number;
    CHECK_NO_PRINT(vec_check_size(vector))

    memcpy(vector->data + ((vector->size - number) * vector->type_size), elements, vector->type_size * number);

    return SCL_SUCCESS;
}

void *vector_get(VECTOR *vector, size_t i)
{
    return vector->data + (vector->type_size * i);
}

void* vec_unlink(VECTOR *vector) {
    void *data = vector->data;
    free(vector);
    return data;
}

void vec_free(VECTOR *vector) {
    free(vector->data);
    free(vector);
}