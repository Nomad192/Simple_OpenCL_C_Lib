#ifndef SIMPLE_OPENCL_C_LIB__SCL_LOAD_SOURCE_H
#define SIMPLE_OPENCL_C_LIB__SCL_LOAD_SOURCE_H

#include "scl_vector.h"

scl_status load_source(VECTOR *sources, const char *filename);
char *scl_get_source(VECTOR *sources, size_t i);
void free_source(VECTOR *sources);

#endif //SIMPLE_OPENCL_C_LIB__SCL_LOAD_SOURCE_H
