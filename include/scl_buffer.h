#ifndef SIMPLE_OPENCL_C_LIB__SCL_BUFFER_H
#define SIMPLE_OPENCL_C_LIB__SCL_BUFFER_H

#include <CL/cl.h>

#include "scl_struct.h"
#include "scl_types.h"

scl_status
scl_buffer_create_return_errcode(SCL *scl, cl_context context, cl_mem_flags flags, size_t size, void *host_ptr,
                                 cl_mem *buffer_ptr);

void scl_buffer_free(cl_mem buffer);

#endif //SIMPLE_OPENCL_C_LIB__SCL_BUFFER_H
