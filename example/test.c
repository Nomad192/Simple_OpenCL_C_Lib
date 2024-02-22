#include <CL/cl.h>

#include <stdio.h>
#include <inttypes.h>
#include "SCL.h"

const scl_number PLATFORM_NUMBER = 0;
const scl_number DEVICE_NUMBER = 0;

void print_init_info(SCL *scl);

int main(void) {
    SCL *scl = scl_create();
    if (scl == NULL) {
        fprintf(stderr, "main. SCL not create.");
        return -1;
    }

    CHECK_AND_PRINT(scl, scl_init(scl, PLATFORM_NUMBER, DEVICE_NUMBER))
    print_init_info(scl);
    CHECK_AND_PRINT(scl, load_source(scl, "main.cl"))

    printf("source - \"%s\"\n\n", (* (char **)vector_get(scl->sources, 0)));

    cl_int errcode_ret = 0;
    cl_context context = clCreateContext(NULL, 1, scl->devices, NULL, NULL, &errcode_ret);
    printf("context status: %" PRId32 "\n", errcode_ret);
    cl_program program = clCreateProgramWithSource(context, scl->sources->size, scl->sources->data, NULL, &errcode_ret);
    printf("program status: %d\n", errcode_ret);
    cl_int status_build = clBuildProgram(program, 1, scl->devices, "", NULL, NULL);

    char arg[1000] = "\0";
    size_t n = 0;

    clGetProgramBuildInfo(program, scl->device_id, CL_PROGRAM_BUILD_LOG, 1000, arg, &n);

    printf("build log size: %zu\n", n);
    printf("build log: \"%s\"\n", arg);
    printf("status_build: %d\n", status_build);

    scl_free(scl);

    return 0;
}

void print_init_info(SCL *scl) {
    printf("Platform name: %s\n", scl->platform_name);
    printf("Device name: %s\n", scl->device_name);
    printf("\n");
    printf("platform_id: %" PRIdPTR "\n", (intptr_t) scl->platform_id);
    printf("device_id: %" PRIdPTR "\n", (intptr_t) scl->device_id);
    printf("\n");
}
