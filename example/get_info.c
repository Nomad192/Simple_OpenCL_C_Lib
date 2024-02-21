#include <CL/cl.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

int main(void) {
    cl_int  status;
    size_t  str_info_size;
    char* str_info;
    cl_uint uint_info;

    cl_uint         num_platforms;
    cl_platform_id* platforms;

    cl_uint       num_devices;
    cl_device_id* devices;

    status = clGetPlatformIDs(0, NULL, &num_platforms);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "Failed to get the number of platforms.\n");
        return -1;
    }

    if (num_platforms > 0) {
        fprintf(stdout, "* The number of platforms: %" PRId32 "\n", num_platforms);
    }
    else {
        fprintf(stderr, "The number of platforms is zero.\n");
        return -1;
    }

    platforms
        = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
    clGetPlatformIDs(num_platforms, platforms, NULL);

    for (int i = 0; i < num_platforms; ++i) {
        fprintf(stdout, "  -----------------------------------------------\n");
        fprintf(stdout, "  Platform-%d\n", i);

        clGetPlatformInfo(
            platforms[i], CL_PLATFORM_NAME, 0, NULL, &str_info_size);
        str_info = (char*)malloc(str_info_size);
        clGetPlatformInfo(
            platforms[i], CL_PLATFORM_NAME, str_info_size, str_info, NULL);
        fprintf(stdout, "  * Platform: %s\n", str_info);
        free(str_info);

        clGetPlatformInfo(
            platforms[i], CL_PLATFORM_PROFILE, 0, NULL, &str_info_size);
        str_info = (char*)malloc(str_info_size);
        clGetPlatformInfo(
            platforms[i], CL_PLATFORM_PROFILE, str_info_size, str_info, NULL);
        fprintf(stdout, "  * Profile: %s\n", str_info);
        free(str_info);

        clGetPlatformInfo(
            platforms[i], CL_PLATFORM_VERSION, 0, NULL, &str_info_size);
        str_info = (char*)malloc(str_info_size);
        clGetPlatformInfo(
            platforms[i], CL_PLATFORM_VERSION, str_info_size, str_info, NULL);
        fprintf(stdout, "  * %s\n", str_info);
        free(str_info);

        status = clGetDeviceIDs(
            platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
        if (status != CL_SUCCESS) {
            fprintf(stderr, "Failed to get the number of devices in the platform %d.\n", i);
            continue;
        }

        if (num_devices > 0) {
            fprintf(stdout, "  * The number of devices: %" PRIu32 "\n", num_devices);
        }
        else {
            fprintf(stderr, "Platform-%d has no devices.\n", i);
            continue;
        }

        devices = (cl_device_id*)malloc(sizeof(cl_device_id) * num_devices);
        clGetDeviceIDs(
            platforms[i], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

        for (int j = 0; j < num_devices; ++j) {
            fprintf(stdout, "    =================================================\n");
            fprintf(stdout, "    Device-%d\n", j);

            clGetDeviceInfo(
                devices[j], CL_DEVICE_NAME, 0, NULL, &str_info_size);
            str_info = (char*)malloc(str_info_size);
            clGetDeviceInfo(
                devices[j], CL_DEVICE_NAME, str_info_size, str_info, NULL);
            fprintf(stdout, "    * name: %s\n", str_info);
            free(str_info);

            clGetDeviceInfo(devices[j],
                CL_DEVICE_MAX_COMPUTE_UNITS,
                sizeof(uint_info),
                &uint_info,
                NULL);
            fprintf(stdout, "    * Max Compute Units: %" PRIu32 "\n", uint_info);

            clGetDeviceInfo(devices[j],
                CL_DEVICE_MAX_CLOCK_FREQUENCY,
                sizeof(uint_info),
                &uint_info,
                NULL);
            fprintf(stdout, "    * Max Clock freq: %" PRIu32 "\n", uint_info);

            fprintf(stdout, "    =================================================\n");
        }
        fprintf(stdout, "  -----------------------------------------------\n");
    }

    free(devices);
    free(platforms);
    return 0;
}