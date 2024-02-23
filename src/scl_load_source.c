#include "scl_load_source.h"

#include <stdlib.h>
#include <stdio.h>

#include "scl_tools.h"
#include "scl_vector.h"

scl_status read_file(const char *filename, char **result);

scl_status load_source(VECTOR *sources, const char *filename) {
    char* file;
    if(read_file(filename, &file) != SCL_SUCCESS) {
        return DEFAULT_ERROR;
    }
    if(vec_add(sources, &file, 1) != SCL_SUCCESS) {
        fprintf(stderr, "FAIL load_source. error realloc.\n");
        free(file);
        return DEFAULT_ERROR;
    }
    return SCL_SUCCESS;
}

char *scl_get_source(VECTOR *sources, size_t i) {
    return *(char **) vector_get(sources, i);
}

void free_source(VECTOR *sources) {
    for (size_t i = 0; i < sources->length; ++i)
        free(scl_get_source(sources, i));
    vec_free(sources);
}

#define INITIAL_BUFFER_SIZE 1024

scl_status read_file(const char *filename, char **result) {
    FILE *file = fopen(filename, "rt");
    if (file == NULL) {
        fprintf(stderr, "FAIL read_file. file \"%s\" not open.\n", filename);
        return DEFAULT_ERROR;
    }

    VECTOR *buffer = vec_create(sizeof(char), INITIAL_BUFFER_SIZE);

    if (buffer == NULL) {
        fprintf(stderr, "FAIL read_file. error malloc.\n");
        fclose(file);
        return DEFAULT_ERROR;
    }

    while (feof(file) == 0) {
        if (vec_check_size(buffer) != SCL_SUCCESS) {
            fprintf(stderr, "FAIL read_file. error realloc.\n");
            vec_free(buffer);
            fclose(file);
            return DEFAULT_ERROR;
        }

        size_t bytes_read = fread(buffer->data + (buffer->length * sizeof(char)), sizeof(char),
                                  buffer->real_size - buffer->length, file);
        if (ferror(file)) {
            fprintf(stderr, "FAIL read_file. error reading file.\n");
            vec_free(buffer);
            fclose(file);
            return DEFAULT_ERROR;
        }

        buffer->length += bytes_read;
    }
    char end = '\0';
    if (vec_add(buffer, &end, 1) != SCL_SUCCESS) {
        fprintf(stderr, "FAIL read_file. error realloc.\n");
        vec_free(buffer);
        fclose(file);
        return DEFAULT_ERROR;
    }

    if (vec_cut(buffer) != SCL_SUCCESS) {
        fprintf(stderr, "FAIL read_file. error realloc.\n");
        vec_free(buffer);
        fclose(file);
        return DEFAULT_ERROR;
    }

    *result = (char *) vec_unlink(buffer);
    fclose(file);

    return SCL_SUCCESS;
}
