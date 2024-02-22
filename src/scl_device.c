#include "scl_device.h"

#include <CL/cl.h>

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

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