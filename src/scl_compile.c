#include "scl_compile.h"

#include <stdio.h>

scl_status compile(SCL *scl) {
    cl_int status;
    scl->context = clCreateContext(NULL, scl->num_devices, scl->devices, NULL, NULL, &status);
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL compile. Failed to get context.\n");
        return SCL_OPENCL_ERROR;
    }

    scl->program = clCreateProgramWithSource(scl->context, scl->sources->size, scl->sources->data, NULL, &status);
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL compile. Failed to get program.\n");
        return SCL_OPENCL_ERROR;
    }

    status = clBuildProgram(scl->program, scl->num_devices, scl->devices, "", NULL, NULL);
    scl_status get_build_log_status = get_build_log(scl);

    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        if (get_build_log_status != SCL_SUCCESS) {
            sprintf(scl->error, "FAIL compile. Failed to compile program. Build log failed to get!\n");
            return SCL_OPENCL_ERROR;
        } else {
            sprintf(scl->error, "FAIL compile. Failed to compile program. Build log: \"%s\"\n", scl->build_log);
            return SCL_OPENCL_ERROR;
        }
    } else {
        if (get_build_log_status != SCL_SUCCESS) {
            sprintf(scl->error, "FAIL compile. Failed to get build log.\n");
            return get_build_log_status;
        }
    }

    return SCL_SUCCESS;
}

scl_status get_build_log(SCL *scl) {
    if (scl->build_log != NULL) {
        free(scl->build_log);
        scl->build_log = NULL;
    }

    cl_int status;
    size_t str_info_size;
    status = clGetProgramBuildInfo(scl->program, scl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &str_info_size);
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL get_build_log. error get CL_PROGRAM_BUILD_LOG size.\n");
        return SCL_OPENCL_ERROR;
    }
    scl->build_log = (char *) malloc(str_info_size);
    if (scl->build_log == NULL) {
        sprintf(scl->error, "FAIL get_build_log. error malloc.\n");
        return SCL_OUT_OF_MEMORY;
    }
    status = clGetProgramBuildInfo(scl->program, scl->device_id, CL_PROGRAM_BUILD_LOG, str_info_size, scl->build_log, NULL);
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL get_build_log. error get CL_PROGRAM_BUILD_LOG.\n");
        free(scl->build_log);
        scl->build_log = NULL;
        return SCL_OPENCL_ERROR;
    }

    return SCL_SUCCESS;
}
