#include "../include/init.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include <CL/cl.h>

init_status get_platform_id(cl_platform_id** platforms, cl_platform_id* platform_id, init_number platform_number)
{
    cl_int status;
    cl_uint num_platforms;

    status = clGetPlatformIDs(0, NULL, &num_platforms);
    if (status != CL_SUCCESS) {
        printf("FAIL get_platform_id. 1. Failed to get the number of platforms.\n");
        return INIT_ERROR;
    }

    if (num_platforms == 0) {
        printf("FAIL get_platform_id. 2. The number of platforms is zero.\n");
        return INIT_ERROR;
    }

    if (platform_number >= num_platforms)
    {
        printf("FAIL get_platform_id. 3. The platform_number >= num_platforms.\n");
        return INIT_ERROR;
    }

    *platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
    if (*platforms == NULL) {
        printf("FAIL get_platform_id. 4. Failed platforms malloc.\n");
        return INIT_ERROR;
    }

    status = clGetPlatformIDs(num_platforms, *platforms, NULL);
    if (status != CL_SUCCESS) {
        printf("FAIL get_platform_id. 5. Failed to get platforms.\n");
        return INIT_ERROR;
    }

    *platform_id = (*platforms)[platform_number];

    return INIT_SUCCESS;
}

init_status get_device_id(cl_platform_id platform_id, cl_device_id** devices, cl_device_id* device_id, init_number device_number)
{
    cl_int status;
    cl_uint num_devices;

    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
    if (status != CL_SUCCESS) {
        printf("FAIL get_device_id. 1. Failed to get the number of devices in the platform_id %" PRIdPTR ".\n", (intptr_t) platform_id);
        return INIT_ERROR;
    }

    if (num_devices == 0) {
        printf("FAIL get_device_id. 2. The number of devices in the platform_id %" PRIdPTR " is zero.\n", (intptr_t) platform_id);
        return INIT_ERROR;
    }

    if (device_number >= num_devices)
    {
        printf("FAIL get_device_id. 3. The device_number >= num_devices.\n");
        return INIT_ERROR;
    }

    *devices = (cl_device_id*)malloc(sizeof(cl_device_id) * num_devices);
    if (*devices == NULL) {
        printf("FAIL get_device_id. 4. Failed platforms devices.\n");
        return INIT_ERROR;
    }

    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, num_devices, *devices, NULL);
    if (status != CL_SUCCESS) {
        printf("FAIL get_device_id. 5. Failed to get devices.\n");
        return INIT_ERROR;
    }

    *device_id = (*devices)[device_number];

    return INIT_SUCCESS;
}

init_status print_platform_name(cl_platform_id platform_id) {
    size_t  str_info_size;
    clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 0, NULL, &str_info_size);
    char* str_info = (char*)malloc(str_info_size);
    if (str_info == NULL) {
        printf("FAIL print_platform_name. 1. error malloc.\n");
        return INIT_OUT_OF_MEMORY;
    }
    clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, str_info_size, str_info, NULL);
    printf("Platform: %s\n", str_info);
    free(str_info);

    return INIT_SUCCESS;
}

init_status print_device_name(cl_device_id device_id) {
    size_t  str_info_size;
    clGetDeviceInfo(device_id, CL_DEVICE_NAME, 0, NULL, &str_info_size);
    char* str_info = (char*)malloc(str_info_size);
    if (str_info == NULL) {
        printf("FAIL print_device_name. 1. error malloc.\n");
        return INIT_OUT_OF_MEMORY;
    }
    printf("print_device_name id: %" PRIdPTR "\n", (intptr_t) device_id);
    clGetDeviceInfo(device_id, CL_DEVICE_NAME, str_info_size, str_info, NULL);
    printf("Device: %s\n", str_info);
    free(str_info);

    return INIT_SUCCESS;
}
