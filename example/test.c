#include <stdio.h>
#include <inttypes.h>
#include "SCL.h"

const scl_number PLATFORM_NUMBER = 0;
const scl_number DEVICE_NUMBER = 0;

void print_init_info(SCL *scl);

void print_source(SCL *scl);

void print_build_log(SCL *scl);

int main(void) {
    SCL *scl = scl_create();
    if (scl == NULL) {
        fprintf(stderr, "main. SCL not create.");
        return -1;
    }

    CHECK_AND_PRINT(scl, scl_init(scl, PLATFORM_NUMBER, DEVICE_NUMBER))
    print_init_info(scl);
    CHECK_AND_PRINT(scl, load_source(scl, "main.cl"))
    print_source(scl);
    CHECK_AND_PRINT(scl, compile(scl))
    print_build_log(scl);

    printf("Build success.");

    cl_kernel kernel = clCreateKernel(scl->program, "APlusB", NULL);

    cl_mem a_mem = clCreateBuffer(scl->context, CL_MEM_READ_ONLY, sizeof(cl_int), NULL, NULL);
    cl_mem b_mem = clCreateBuffer(scl->context, CL_MEM_READ_ONLY, sizeof(cl_int), NULL, NULL);
    cl_mem c_mem = clCreateBuffer(scl->context, CL_MEM_WRITE_ONLY, sizeof(cl_int), NULL, NULL);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &a_mem);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &b_mem);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &c_mem);

    cl_command_queue command_queue = clCreateCommandQueue(scl->context, scl->device_id, 0, NULL);

    cl_int a = 2, b = 3;
    clEnqueueWriteBuffer(command_queue, a_mem, CL_FALSE, 0, sizeof(cl_int), &a, 0, NULL, NULL);
    clEnqueueWriteBuffer(command_queue, b_mem, CL_FALSE, 0, sizeof(cl_int), &b, 0, NULL, NULL);

    size_t one = 1;
    clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &one, NULL, 0, NULL, NULL);

    cl_int c;
    clEnqueueReadBuffer(command_queue, c_mem, CL_TRUE, 0, sizeof(cl_int), &c, 0, NULL, NULL);

    printf("Executed %d + %d successfully, got %d (expected %d).\n", a, b, c, a + b);

    clReleaseMemObject(a_mem);
    clReleaseMemObject(b_mem);
    clReleaseMemObject(c_mem);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(command_queue);

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

void print_source(SCL *scl) {
    printf("==================================================================================\n");
    printf("----------------------------------------------------------------------------------");
    for (size_t i = 0; i < scl->sources->size; ++i) {
        printf("\nsource:\"\n%s\"\n", scl_get_source(scl, i));
        printf("----------------------------------------------------------------------------------");
    }
    printf("\n");
    printf("==================================================================================\n\n");
}

void print_build_log(SCL *scl) {
    printf("Build log: \"%s\"\n\n", scl->build_log);
}
