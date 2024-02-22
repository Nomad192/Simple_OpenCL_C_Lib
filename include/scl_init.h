#ifndef SIMPLE_OPENCL_C_LIB__SCL_INIT_H
#define SIMPLE_OPENCL_C_LIB__SCL_INIT_H

#include <CL/cl.h>

#include "scl_types.h"
#include "scl_struct.h"

SCL *scl_create();

scl_status scl_init(SCL *scl, scl_number target_platform_number, scl_number target_device_number);

void scl_free(SCL *scl);

#endif //SIMPLE_OPENCL_C_LIB__SCL_INIT_H
