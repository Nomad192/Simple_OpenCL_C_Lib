#ifndef SIMPLE_OPENCL_C_LIB__SCL_STRUCT_H
#define SIMPLE_OPENCL_C_LIB__SCL_STRUCT_H

#include <CL/cl.h>

#include "scl_types.h"
#include "scl_vector.h"

typedef struct SCL_Struct {
    scl_number platform_number;
    scl_number device_number;

    cl_uint num_platforms;
    cl_platform_id *platforms;
    cl_platform_id platform_id;
    char *platform_name;

    cl_uint num_devices;
    cl_device_id *devices;
    cl_device_id device_id;
    char *device_name;

    VECTOR *sources;

    cl_context context;
    cl_program program;

    char *build_log;

    char *error;
    cl_int cl_errcode;
} SCL;

#endif //SIMPLE_OPENCL_C_LIB__SCL_STRUCT_H
