#include "scl_platform.h"

#include <CL/cl.h>

#include <stdio.h>
#include <stdlib.h>

scl_status get_platform_id(SCL *scl, scl_number target_platform_number) {
    if (scl->platforms != NULL) {
        free(scl->platforms);
        scl->platforms = NULL;
    }
    scl->platform_number = -1;
    scl->num_platforms = -1;
    scl->platform_id = NULL;

    cl_int status;
    status = clGetPlatformIDs(0, NULL, &(scl->num_platforms));
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        scl->num_platforms = -1;
        sprintf(scl->error, "FAIL get_platform_id. Failed to get the number of platforms.\n");
        return SCL_OPENCL_ERROR;
    }

    if (scl->num_platforms == 0) {
        scl->num_platforms = -1;
        sprintf(scl->error, "FAIL get_platform_id. The number of platforms is zero.\n");
        return SCL_ERROR;
    }

    if (target_platform_number >= scl->num_platforms) {
        scl->num_platforms = -1;
        sprintf(scl->error, "FAIL get_platform_id. The platform_number >= num_platforms.\n");
        return SCL_ERROR;
    }

    scl->platforms = (cl_platform_id *) malloc(sizeof(cl_platform_id) * scl->num_platforms);
    if (scl->platforms == NULL) {
        sprintf(scl->error, "FAIL get_platform_id. Failed platforms malloc.\n");
        return SCL_ERROR;
    }

    status = clGetPlatformIDs(scl->num_platforms, scl->platforms, NULL);
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL get_platform_id. Failed to get platforms.\n");
        return SCL_OPENCL_ERROR;
    }

    scl->platform_number = target_platform_number;
    scl->platform_id = scl->platforms[target_platform_number];

    return SCL_SUCCESS;
}

scl_status get_platform_name(SCL *scl) {
    if (scl->platform_name != NULL) {
        free(scl->platform_name);
        scl->platform_name = NULL;
    }

    cl_int status;
    size_t str_info_size;
    status = clGetPlatformInfo(scl->platform_id, CL_PLATFORM_NAME, 0, NULL, &str_info_size);
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL get_platform_name. error get CL_PLATFORM_NAME size.\n");
        return SCL_OPENCL_ERROR;
    }
    scl->platform_name = (char *) malloc(str_info_size);
    if (scl->platform_name == NULL) {
        sprintf(scl->error, "FAIL get_platform_name. error malloc.\n");
        return SCL_OUT_OF_MEMORY;
    }
    status = clGetPlatformInfo(scl->platform_id, CL_PLATFORM_NAME, str_info_size, scl->platform_name, NULL);
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL get_platform_name. error get CL_PLATFORM_NAME.\n");
        free(scl->platform_name);
        scl->platform_name = NULL;
        return SCL_OPENCL_ERROR;
    }

    return SCL_SUCCESS;
}
