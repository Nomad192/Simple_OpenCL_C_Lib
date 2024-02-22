#ifndef SIMPLE_OPENCL_C_LIB__SCL_INIT_H
#define SIMPLE_OPENCL_C_LIB__SCL_INIT_H

#include <CL/cl.h>

#include "scl_types.h"
#include "scl_struct.h"

void scl_print_error(SCL *scl);

#define CHECK_AND_PRINT(SCL_STRUCT, FUNC) { \
    scl_status check_status = FUNC; if (check_status != SCL_SUCCESS) \
    { scl_print_error(SCL_STRUCT); return check_status; } \
}

#define CHECK(FUNC) { \
    scl_status check_status = FUNC; if (check_status != SCL_SUCCESS) \
    { return check_status; } \
}

SCL *create();

scl_status init(SCL *scl, scl_number target_platform_number, scl_number target_device_number);

void scl_free(SCL *scl);

#endif //SIMPLE_OPENCL_C_LIB__SCL_INIT_H
