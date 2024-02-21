#include <CL/cl.h>

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "SCL.h"

const init_number PLATFORM_NUMBER = 0;
const init_number DEVICE_NUMBER = 0;

cl_platform_id *g_platforms;
cl_platform_id g_platform_id;

cl_device_id *g_devices;
cl_device_id g_device_id;

int get_and_print_info();

void free_global();

int main(void) {
    init_status local_init_status;

    if (get_and_print_info() != 0) return -1;

    printf("device id from devices: %d\n", (intptr_t) g_devices[0]);

    const char program_code_line_01[] = "kernel void add(global const int *a, global const int *b, global int *c) { *c = *a + *b; }";
    const char *program_code_str = program_code_line_01;


    size_t lengths[1] = {sizeof(program_code_line_01) / sizeof(program_code_line_01[0])};

    cl_int errcode_ret = 0;
    cl_context context = clCreateContext(NULL, 1, g_devices, NULL, NULL, &errcode_ret);
    printf("context status: %" PRIdPTR "\n", errcode_ret);
    cl_program program = clCreateProgramWithSource(context, 1, &program_code_str, lengths, &errcode_ret);
    printf("program status: %d\n", errcode_ret);
    cl_int status_build = clBuildProgram(program, 1, g_devices, "", NULL, NULL);
    cl_program_build_info program_build_info = CL_PROGRAM_BUILD_LOG;

    char arg[1000] = "\0";
    size_t n = 0;

    clGetProgramBuildInfo(program, g_device_id, CL_PROGRAM_BUILD_LOG, 1000, arg, &n);

    printf("build log size: %zu\n", n);
    printf("build log: \"%s\"\n", arg);
    printf("status_build: %d\n", status_build);

    free_global();
    return 0;
}

int get_and_print_info() {
    init_status local_init_status;

    local_init_status = get_platform_id(&g_platforms, &g_platform_id, PLATFORM_NUMBER);
    if (local_init_status != INIT_SUCCESS) {
        free_global();
        return -1;
    }
    local_init_status = print_platform_name(g_platform_id);
    if (local_init_status != INIT_SUCCESS) {
        free_global();
        return -1;
    }
    printf("platform_id: %" PRIdPTR "\n", (intptr_t) g_platform_id);

    local_init_status = get_device_id(g_platform_id, &g_devices, &g_device_id, DEVICE_NUMBER);
    if (local_init_status != INIT_SUCCESS) {
        free_global();
        return -1;
    }
    local_init_status = print_device_name(g_device_id);
    if (local_init_status != INIT_SUCCESS) {
        free_global();
        return -1;
    }
    printf("device_id: %" PRIdPTR "\n", (intptr_t) g_device_id);

    return 0;
}

void free_global() {
    free(g_devices);
    free(g_platforms);
}
