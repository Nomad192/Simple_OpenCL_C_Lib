#ifndef SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H
#define SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H

#include "scl_types.h"

#define GET_CL_PARAM_NO_SIZE(TYPE, VARIABLE, TYPE_NUM, VARIABLE_NUM, FUNC_GET_NUM, FUNC_GET_ARRAY) \
{ \
    cl_int errcode; \
    errcode = FUNC_GET_NUM; \
    if (errcode != CL_SUCCESS) { fprintf(stderr, "Error get " #FUNC_GET_NUM "\n"); global_errcode = errcode; goto clean; } \
    if (VARIABLE_NUM == 0) { fprintf(stderr, "Error num is 0. " #FUNC_GET_NUM "\n"); goto clean; } \
    VARIABLE = (TYPE *) malloc(sizeof(TYPE) * VARIABLE_NUM); \
    if (VARIABLE == NULL) { fprintf(stderr, "Error malloc. " #VARIABLE "\n"); goto clean; } \
    errcode = FUNC_GET_ARRAY; \
    if (errcode != CL_SUCCESS) { fprintf(stderr, "Error get " #FUNC_GET_ARRAY "\n"); global_errcode = errcode; goto clean; } \
}

#define GET_CL_PARAM_WITH_SIZE(TYPE, VARIABLE, TYPE_NUM, VARIABLE_NUM, FUNC_GET_NUM, FUNC_GET_ARRAY) TYPE_NUM VARIABLE_NUM; \
GET_CL_PARAM_NO_SIZE(TYPE, VARIABLE, TYPE_NUM, VARIABLE_NUM, FUNC_GET_NUM, FUNC_GET_ARRAY)

#define GET_CL_ARRAY(TYPE, VARIABLE, VARIABLE_NUM, FUNC_GET_NUM, FUNC_GET_ARRAY) \
GET_CL_PARAM_WITH_SIZE(TYPE, VARIABLE, cl_uint, VARIABLE_NUM, FUNC_GET_NUM, FUNC_GET_ARRAY)

#define GET_CL_PARAM(TYPE, VARIABLE, VARIABLE_NUM, FUNC_GET_NUM, FUNC_GET_ARRAY) \
{ \
    GET_CL_PARAM_WITH_SIZE(TYPE, VARIABLE, size_t, VARIABLE_NUM, FUNC_GET_NUM, FUNC_GET_ARRAY) \
}

#define CHECK_CL_ARRAY(VARIABLE_NEED, VARIABLE_NUM) \
{ \
    if (VARIABLE_NEED >= VARIABLE_NUM) { \
        fprintf(stderr, "Error get " #VARIABLE_NEED " >= " #VARIABLE_NUM ", %" PRId32 " >= %" PRId32 "\n", \
        VARIABLE_NEED, VARIABLE_NUM); \
        goto clean; \
    } \
}

#define GET_ID(TYPE, VARIABLE, TARGET_NUM, ARRAY, LEN) TYPE VARIABLE; \
{ \
    CHECK_CL_ARRAY(TARGET_NUM, LEN) \
    VARIABLE = ARRAY[TARGET_NUM]; \
}

#define GET_CL(VARIABLE, FUNC) \
{ \
    cl_int errcode; \
    VARIABLE = FUNC; \
    if (errcode != CL_SUCCESS) { fprintf(stderr, "Error get " #VARIABLE "\n"); global_errcode = errcode; goto clean; } \
}

#define CHECK_CL(FUNC) \
{ \
    cl_int errcode = FUNC; \
    if (errcode != CL_SUCCESS) { fprintf(stderr, "Error get " #FUNC "\n"); global_errcode = errcode; goto clean; } \
}

#define GET(VARIABLE, FUNC) \
{ \
    VARIABLE = FUNC; \
    if (VARIABLE == NULL) { fprintf(stderr, "Error get " #VARIABLE "\n"); global_errcode = DEFAULT_ERROR; goto clean; } \
}

#define BEGIN cl_int global_errcode = DEFAULT_ERROR;

#define ERROR goto clean;

#define FREE_BEG \
    global_errcode = CL_SUCCESS; \
clean:

#define FREE(PTR) CUSTOM_FREE(PTR, free)

#define CUSTOM_FREE(PTR, FUNC) \
{ \
    if (PTR != NULL) \
    { \
        FUNC(PTR);\
        PTR = NULL; \
    } \
}

#define RETURN return global_errcode;

#endif //SIMPLE_OPENCL_C_LIB__SCL_TOOLS_H
