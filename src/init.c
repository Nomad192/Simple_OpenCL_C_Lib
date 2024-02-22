#include "../include/init.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include <CL/cl.h>

SCL *create() {
    SCL *scl = (SCL *) malloc(sizeof(SCL));

    if (scl != NULL) {
        scl->platform_number = -1;
        scl->device_number = -1;

        scl->num_platforms = -1;
        scl->platforms = NULL;
        scl->platform_name = NULL;
        scl->platform_id = NULL;

        scl->num_devices = -1;
        scl->devices = NULL;
        scl->device_name = NULL;
        scl->device_id = NULL;

        scl->error = (char *) malloc(sizeof(char) * 1000);
    }

    return scl;
}

scl_status init(SCL *scl, scl_number target_platform_number, scl_number target_device_number) {
    CHECK(get_platform_id(scl, target_platform_number))
    CHECK(get_platform_name(scl))
    CHECK(get_device_id(scl, target_device_number))
    CHECK(get_device_name(scl))

    return SCL_SUCCESS;
}

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
        scl->num_platforms = -1;
        sprintf(scl->error, "FAIL get_platform_id. Failed to get the number of platforms.\n");
        return SCL_ERROR;
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
        sprintf(scl->error, "FAIL get_platform_id. Failed to get platforms.\n");
        return SCL_ERROR;
    }

    scl->platform_number = target_platform_number;
    scl->platform_id = scl->platforms[target_platform_number];

    return SCL_SUCCESS;
}

scl_status get_device_id(SCL *scl, scl_number target_device_number) {
    if (scl->platforms == NULL) {
        sprintf(scl->error, "FAIL get_device_id. platforms are not initialized.\n");
    }

    if (scl->devices != NULL) {
        free(scl->devices);
        scl->devices = NULL;
    }
    scl->device_number = -1;
    scl->num_devices = -1;
    scl->device_id = NULL;

    cl_int status;
    status = clGetDeviceIDs(scl->platform_id, CL_DEVICE_TYPE_ALL, 0, NULL, &(scl->num_devices));
    if (status != CL_SUCCESS) {
        sprintf(scl->error,
                "FAIL get_device_id. 1. Failed to get the number of devices in the platform_id %" PRIdPTR ".\n",
                (intptr_t) scl->platform_id);
        return SCL_ERROR;
    }

    if (scl->num_devices == 0) {
        sprintf(scl->error, "FAIL get_device_id. 2. The number of devices in the platform_id %" PRIdPTR " is zero.\n",
                (intptr_t) scl->platform_id);
        return SCL_ERROR;
    }

    if (target_device_number >= scl->num_devices) {
        sprintf(scl->error, "FAIL get_device_id. 3. The device_number >= num_devices.\n");
        return SCL_ERROR;
    }

    scl->devices = (cl_device_id *) malloc(sizeof(cl_device_id) * scl->num_devices);
    if (scl->devices == NULL) {
        sprintf(scl->error, "FAIL get_device_id. 4. Failed platforms devices.\n");
        return SCL_ERROR;
    }

    status = clGetDeviceIDs(scl->platform_id, CL_DEVICE_TYPE_ALL, scl->num_devices, scl->devices, NULL);
    if (status != CL_SUCCESS) {
        sprintf(scl->error, "FAIL get_device_id. 5. Failed to get devices.\n");
        return SCL_ERROR;
    }

    scl->device_number = target_device_number;
    scl->device_id = scl->devices[target_device_number];

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
        sprintf(scl->error, "FAIL get_platform_name. error get CL_PLATFORM_NAME size.\n");
        return SCL_ERROR;
    }
    scl->platform_name = (char *) malloc(str_info_size);
    if (scl->platform_name == NULL) {
        sprintf(scl->error, "FAIL get_platform_name. error malloc.\n");
        return SCL_OUT_OF_MEMORY;
    }
    status = clGetPlatformInfo(scl->platform_id, CL_PLATFORM_NAME, str_info_size, scl->platform_name, NULL);
    if (status != CL_SUCCESS) {
        sprintf(scl->error, "FAIL get_platform_name. error get CL_PLATFORM_NAME.\n");
        free(scl->platform_name);
        scl->platform_name = NULL;
        return SCL_ERROR;
    }

    return SCL_SUCCESS;
}

scl_status get_device_name(SCL *scl) {
    if (scl->device_name != NULL) {
        free(scl->device_name);
        scl->device_name = NULL;
    }

    cl_int status;
    size_t str_info_size;
    status = clGetDeviceInfo(scl->device_id, CL_DEVICE_NAME, 0, NULL, &str_info_size);
    if (status != CL_SUCCESS) {
        sprintf(scl->error, "FAIL get_device_name. error get CL_DEVICE_NAME size.\n");
        return SCL_ERROR;
    }
    scl->device_name = (char *) malloc(str_info_size);
    if (scl->device_name == NULL) {
        sprintf(scl->error, "FAIL get_device_name. error malloc.\n");
        return SCL_OUT_OF_MEMORY;
    }
    status = clGetDeviceInfo(scl->device_id, CL_DEVICE_NAME, str_info_size, scl->device_name, NULL);
    if (status != CL_SUCCESS) {
        sprintf(scl->error, "FAIL get_device_name. error get CL_DEVICE_NAME.\n");
        free(scl->device_name);
        scl->device_name = NULL;
        return SCL_ERROR;
    }

    return SCL_SUCCESS;
}

void scl_print_error(SCL *scl) {
    fprintf(stderr, "%s\n", scl->error);
}

void scl_free(SCL *scl) {
    free(scl->error);
    free(scl->devices);
    free(scl->device_name);
    free(scl->platforms);
    free(scl->platform_name);
    free(scl);
}
