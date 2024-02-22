#ifndef SIMPLE_OPENCL_C_LIB__SCL_PLATFORM_H
#define SIMPLE_OPENCL_C_LIB__SCL_PLATFORM_H

#include "scl_types.h"
#include "scl_struct.h"

scl_status get_platform_id(SCL *scl, scl_number target_platform_number);
scl_status get_platform_name(SCL *scl);

#endif //SIMPLE_OPENCL_C_LIB__SCL_PLATFORM_H
