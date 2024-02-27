#include <CL/cl.h>

#include <stdio.h>
#include <inttypes.h>

#include "SCL.h"

const scl_number PLATFORM_NUMBER = 0;
const scl_number DEVICE_NUMBER = 0;

void print_init_info(char *platform_name, char *device_name, cl_platform_id platform_id, cl_device_id device_id);
void print_source(VECTOR *sources);
void print_build_log(char *build_log);

int main(void) {
    BEGIN

    cl_platform_id *platforms = NULL;
    char *platform_name = NULL;
    cl_device_id *devices = NULL;
    char *device_name = NULL;

    VECTOR *sources = NULL;

    cl_context context = NULL;
    cl_program program = NULL;
    char *build_log = NULL;

    cl_kernel kernel = NULL;

    cl_mem a_mem = NULL;
    cl_mem b_mem = NULL;
    cl_mem c_mem = NULL;

    cl_command_queue command_queue = NULL;

    /// ============================================================================================================ ///

    GET_CL_ARRAY(cl_platform_id, platforms, num_platforms
                 , clGetPlatformIDs(0, NULL, &num_platforms)
                 , clGetPlatformIDs(num_platforms, platforms, NULL))
    GET_ID(cl_platform_id, platform_id, PLATFORM_NUMBER, platforms, num_platforms)
    GET_CL_PARAM(char, platform_name, size
                 , clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 0, NULL, &size)
                 , clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, size, platform_name, NULL))

    GET_CL_ARRAY(cl_device_id, devices, num_devices
                 , clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices)
                 , clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, num_devices, devices, NULL))
    GET_ID(cl_device_id, device_id, DEVICE_NUMBER, devices, num_devices)
    GET_CL_PARAM(char, device_name, size
                 , clGetDeviceInfo(device_id, CL_DEVICE_NAME, 0, NULL, &size)
                 , clGetDeviceInfo(device_id, CL_DEVICE_NAME, size, device_name, NULL))

    print_init_info(platform_name, device_name, platform_id, device_id);

    /// ------------------------------------------------------------------------------------------------------------ ///

    GET(sources, vec_create(sizeof(char *), 10))
    CHECK_CL(load_source(sources, "add.cl"))
    print_source(sources);

    /// ------------------------------------------------------------------------------------------------------------ ///

    GET_CL(context, clCreateContext(NULL, num_devices, devices, NULL, NULL, ERRCODE))
    GET_CL(program, clCreateProgramWithSource(context, sources->length, sources->data, NULL, ERRCODE))

    {
        cl_int build_status = clBuildProgram(program, num_devices, devices, "", NULL, NULL);
        GET_CL_PARAM(char, build_log, size
                     , clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &size)
                     , clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, size, build_log, NULL))

        print_build_log(build_log);
        if (build_status != CL_SUCCESS) {
            fprintf(stderr, "Build FAIL.\n");
            ERROR
        }
        printf("Build success.\n\n");
    }

    /// ------------------------------------------------------------------------------------------------------------ ///

    GET_CL(kernel, clCreateKernel(program, "add", ERRCODE))

    GET_CL(a_mem, clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(cl_int), NULL, ERRCODE))
    GET_CL(b_mem, clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(cl_int), NULL, ERRCODE))
    GET_CL(c_mem, clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(cl_int), NULL, ERRCODE))

    CHECK_CL(clSetKernelArg(kernel, 0, sizeof(cl_mem), &a_mem))
    CHECK_CL(clSetKernelArg(kernel, 1, sizeof(cl_mem), &b_mem))
    CHECK_CL(clSetKernelArg(kernel, 2, sizeof(cl_mem), &c_mem))

    GET_CL(command_queue, clCreateCommandQueue(context, device_id, 0, ERRCODE))

    /// ------------------------------------------------------------------------------------------------------------ ///

    cl_int a = 2, b = 3;
    CHECK_CL(clEnqueueWriteBuffer(command_queue, a_mem, CL_FALSE, 0, sizeof(cl_int), &a, 0, NULL, NULL))
    CHECK_CL(clEnqueueWriteBuffer(command_queue, b_mem, CL_FALSE, 0, sizeof(cl_int), &b, 0, NULL, NULL))

    size_t one = 1;
    CHECK_CL(clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &one, NULL, 0, NULL, NULL))

    cl_int c;
    CHECK_CL(clEnqueueReadBuffer(command_queue, c_mem, CL_TRUE, 0, sizeof(cl_int), &c, 0, NULL, NULL))

    if (a + b != c) {
        fprintf(stderr, "Executed successfully, BUT not correct.\n");
        fprintf(stderr, "Executed %d + %d successfully, got %d (expected %d).\n", a, b, c, a + b);
        ERROR
    }

    printf("Executed %d + %d successfully, got %d (expected %d).\n", a, b, c, a + b);

    /// ============================================================================================================ ///

    FREE_BEG
    CUSTOM_FREE(command_queue, clReleaseCommandQueue)
    CUSTOM_FREE(c_mem, clReleaseMemObject)
    CUSTOM_FREE(b_mem, clReleaseMemObject)
    CUSTOM_FREE(a_mem, clReleaseMemObject)
    CUSTOM_FREE(kernel, clReleaseKernel)
    FREE(build_log)
    CUSTOM_FREE(program, clReleaseProgram)
    CUSTOM_FREE(context, clReleaseContext)
    CUSTOM_FREE(sources, free_source)
    FREE(device_name)
    FREE(devices)
    FREE(platform_name)
    FREE(platforms)
    RETURN
}

void print_init_info(char *platform_name, char *device_name, cl_platform_id platform_id, cl_device_id device_id) {
    printf("Platform name: %s\n", platform_name);
    printf("Device name: %s\n", device_name);
    printf("\n");
    printf("platform_id: %" PRIdPTR "\n", (intptr_t) platform_id);
    printf("device_id: %" PRIdPTR "\n", (intptr_t) device_id);
    printf("\n");
}

void print_source(VECTOR *sources) {
    printf("==================================================================================\n");
    printf("----------------------------------------------------------------------------------");
    for (size_t i = 0; i < sources->length; ++i) {
        printf("\nsource:\"\n%s\"\n", *((char **) vector_get(sources, i)));
        printf("----------------------------------------------------------------------------------");
    }
    printf("\n");
    printf("==================================================================================\n\n");
}

void print_build_log(char *build_log) {
    printf("Build log: \"%s\"\n\n", build_log);
}
