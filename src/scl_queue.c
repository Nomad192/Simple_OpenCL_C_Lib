#include "scl_queue.h"

#include <stdio.h>

scl_status
scl_queue_create_return_errcode(SCL *scl, cl_context context, cl_device_id device_id, cl_command_queue_properties properties,
                                cl_command_queue *command_queue_ptr) {
    cl_int status;
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, properties, &status);
    if (status != CL_SUCCESS)
    {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL scl_queue_create_return_errcode. Failed to create command queue.\n");
        return SCL_OPENCL_ERROR;
    }
    *command_queue_ptr = command_queue;
    return SCL_SUCCESS;
}

void scl_queue_free(cl_command_queue command_queue) {
    clReleaseCommandQueue(command_queue);
}
