#ifndef SIMPLE_OPENCL_C_LIB_INIT_H
#define SIMPLE_OPENCL_C_LIB_INIT_H

#include <CL/cl.h>

/******************************************************************************/

typedef signed __int32 init_status;
typedef unsigned int init_number;

/* Error Codes */
#define INIT_SUCCESS            (0)
#define INIT_ERROR				(-1)
#define INIT_OUT_OF_MEMORY      (-2)

/******************************************************************************/

init_status get_platform_id(cl_platform_id** platforms, cl_platform_id* platform_id, init_number platform_number);
init_status get_device_id(cl_platform_id platform_id, cl_device_id** devices, cl_device_id* device_id, init_number device_number);

init_status print_platform_name(cl_platform_id platform_id);
init_status print_device_name(cl_device_id device_id);

#endif //SIMPLE_OPENCL_C_LIB_INIT_H
