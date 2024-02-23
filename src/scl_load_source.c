#include "scl_load_source.h"

#include <stdlib.h>
#include <stdio.h>

#include "scl_tools.h"
#include "scl_vector.h"

scl_status read_file(SCL *scl, const char *filename, char **result);

scl_status load_source(SCL *scl, const char *filename) {
    char* file;
    CHECK_NO_PRINT(read_file(scl, filename, &file))
    if(vec_add(scl->sources, &file, 1) != SCL_SUCCESS) {
        sprintf(scl->error, "FAIL load_source. error realloc.\n");
        free(file);
        return SCL_OUT_OF_MEMORY;
    }
    return SCL_SUCCESS;
}

#define INITIAL_BUFFER_SIZE 1024

scl_status read_file(SCL *scl, const char *filename, char **result) {
    FILE *file = fopen(filename, "rt");
    if (file == NULL) {
        sprintf(scl->error, "FAIL read_file. file \"%s\" not open.\n", filename);
        return SCL_FILE_NOT_OPEN;
    }

    VECTOR *buffer = vec_create(sizeof(char), INITIAL_BUFFER_SIZE);

    if (buffer == NULL) {
        sprintf(scl->error, "FAIL read_file. error malloc.\n");
        fclose(file);
        return SCL_OUT_OF_MEMORY;
    }

    while (feof(file) == 0) {
        if (vec_check_size(buffer) != SCL_SUCCESS) {
            sprintf(scl->error, "FAIL read_file. error realloc.\n");
            vec_free(buffer);
            fclose(file);
            return SCL_OUT_OF_MEMORY;
        }

        size_t bytes_read = fread(buffer->data + (buffer->size * sizeof(char)), sizeof(char),
                                  buffer->real_size - buffer->size, file);
        if (ferror(file)) {
            sprintf(scl->error, "FAIL read_file. error reading file.\n");
            vec_free(buffer);
            fclose(file);
            return SCL_ERROR;
        }

        buffer->size += bytes_read;
    }
    char end = '\0';
    if (vec_add(buffer, &end, 1) != SCL_SUCCESS) {
        sprintf(scl->error, "FAIL read_file. error realloc.\n");
        vec_free(buffer);
        fclose(file);
        return SCL_OUT_OF_MEMORY;
    }

    if (vec_cut(buffer) != SCL_SUCCESS) {
        sprintf(scl->error, "FAIL read_file. error realloc.\n");
        vec_free(buffer);
        fclose(file);
        return SCL_OUT_OF_MEMORY;
    }

    *result = (char *) vec_unlink(buffer);
    fclose(file);

    return SCL_SUCCESS;
}