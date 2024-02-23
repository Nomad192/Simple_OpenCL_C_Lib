#ifndef SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H
#define SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H

#include "scl_struct.h"

char *scl_get_source(SCL *scl, size_t i);
void scl_print_error(SCL *scl);

#define CHECK_AND_PRINT(SCL_STRUCT, FUNC) { \
    scl_status check_status = FUNC; if (check_status != SCL_SUCCESS) \
    { scl_print_error(SCL_STRUCT); return check_status; } \
}

#define CHECK(FUNC) { \
    scl_status check_status = FUNC; if (check_status != SCL_SUCCESS) \
    { return check_status; } \
}

#endif //SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H
