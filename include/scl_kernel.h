#ifndef SIMPLE_OPENCL_C_LIB__SCL_KERNEL_H
#define SIMPLE_OPENCL_C_LIB__SCL_KERNEL_H

#include <CL/cl.h>

#include "scl_vector.h"
#include "scl_struct.h"

//typedef struct SCL_KERNEL_STRUCT {
//    cl_context context;
//    cl_device_id device_id;
//    cl_kernel kernel;
//
//    VECTOR *buffers;
//} SCL_KERNEL;
//
//SCL_KERNEL *scl_kernel_create(cl_context context, cl_device_id device_id);
//
//scl_status
//scl_kernel_create_return_errcode(SCL *scl, cl_context context, cl_device_id device_id, SCL_KERNEL **scl_kernel_ptr);
//
//scl_status scl_kernel_init(SCL *scl, SCL_KERNEL *scl_kernel, cl_program program, const char *kernel_name);
//
//cl_mem scl_kernel_get_buffer(SCL_KERNEL *scl_kernel, size_t buf_id);
//
//void scl_kernel_free(SCL_KERNEL *scl_kernel);

scl_status scl_kernel_create_return_errcode(SCL *scl, cl_program program, const char *kernel_name, cl_kernel *kernel_ptr);

void scl_kernel_free(cl_kernel kernel);

#endif //SIMPLE_OPENCL_C_LIB__SCL_KERNEL_H
