#include "scl_kernel.h"

#include <stdio.h>
//
//SCL_KERNEL *scl_kernel_create(cl_context context, cl_device_id device_id) {
//    SCL_KERNEL *scl_kernel = (SCL_KERNEL *) malloc(sizeof(SCL_KERNEL));
//
//    if (scl_kernel != NULL) {
//        scl_kernel->context = context;
//        scl_kernel->device_id = device_id;
//    }
//
//    return scl_kernel;
//}
//
//scl_status
//scl_kernel_create_return_errcode(SCL *scl, cl_context context, cl_device_id device_id, SCL_KERNEL **scl_kernel_ptr) {
//    SCL_KERNEL *scl_kernel = scl_kernel_create(context, device_id);
//    if (scl_kernel == NULL) {
//        sprintf(scl->error, "FAIL scl_kernel_create_return_errcode. Fail malloc.\n");
//        return SCL_OUT_OF_MEMORY;
//    }
//    *scl_kernel_ptr = scl_kernel;
//    return SCL_SUCCESS;
//}
//
//scl_status scl_kernel_init(SCL *scl, SCL_KERNEL *scl_kernel, cl_program program, const char *kernel_name) {
//    cl_int status = 0;
//    scl_kernel->kernel = clCreateKernel(program, kernel_name, &status);
//    if (status != CL_SUCCESS) {
//        scl->cl_errcode = status;
//        sprintf(scl->error, "FAIL scl_kernel_init. Failed to create kernel.\n");
//        return SCL_OPENCL_ERROR;
//    }
//    return SCL_SUCCESS;
//}
//
//void scl_kernel_free(SCL_KERNEL *scl_kernel) {
//    clReleaseKernel(scl_kernel->kernel);
//    free(scl_kernel);
//}


scl_status scl_kernel_create_return_errcode(SCL *scl, cl_program program, const char *kernel_name, cl_kernel *kernel_ptr){
    cl_int status;
    cl_kernel kernel = clCreateKernel(program, kernel_name, &status);
    if (status != CL_SUCCESS) {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL scl_kernel_create_return_errcode. Failed to create kernel.\n");
        return SCL_OPENCL_ERROR;
    }
    *kernel_ptr = kernel;
    return SCL_SUCCESS;
}

void scl_kernel_free(cl_kernel kernel) {
    clReleaseKernel(kernel);
}