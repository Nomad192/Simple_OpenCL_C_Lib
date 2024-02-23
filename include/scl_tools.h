#ifndef SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H
#define SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H

#include "scl_struct.h"

char *scl_get_source(SCL *scl, size_t i);

void scl_print_error(SCL *scl);

#define GET(CREATE, SCL_STRUCT, FUNC) CREATE; \
{ \
    scl_status check_status = FUNC; if (check_status != SCL_SUCCESS) \
    { scl_print_error(SCL_STRUCT); return check_status; } \
}

#define GET_CL(TYPE, VARIABLE, FUNC) TYPE VARIABLE; \
{ \
    cl_int errcode; \
    VARIABLE = FUNC; \
    if (errcode != CL_SUCCESS) { fprintf(stderr, "Error get " #VARIABLE "\n"); return errcode; } \
}

#define CHECK_CL(FUNC) \
{ \
    cl_int errcode = FUNC; \
    if (errcode != CL_SUCCESS) { fprintf(stderr, "Error get " #FUNC "\n"); return errcode; } \
}

#define CHECK(SCL_STRUCT, FUNC) { \
    scl_status check_status = FUNC; if (check_status != SCL_SUCCESS) \
    { scl_print_error(SCL_STRUCT); return check_status; } \
}

#define CHECK_NO_PRINT(FUNC) { \
    scl_status check_status = FUNC; if (check_status != SCL_SUCCESS) \
    { return check_status; } \
}

#endif //SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H
