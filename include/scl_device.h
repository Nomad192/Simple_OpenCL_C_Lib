#ifndef SIMPLE_OPENCL_C_LIB__SCL_DEVICE_H
#define SIMPLE_OPENCL_C_LIB__SCL_DEVICE_H

#include "scl_types.h"
#include "scl_struct.h"

scl_status get_device_id(SCL *scl, scl_number target_device_number);
scl_status get_device_name(SCL *scl);

#endif //SIMPLE_OPENCL_C_LIB__SCL_DEVICE_H
