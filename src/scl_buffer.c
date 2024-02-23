#include "scl_buffer.h"

#include <stdio.h>


scl_status
scl_buffer_create_return_errcode(SCL *scl, cl_context context, cl_mem_flags flags, size_t size, void *host_ptr,
                                 cl_mem *buffer_ptr)
{
    cl_int status;
    cl_mem buffer = clCreateBuffer(context, flags, size, host_ptr, &status);
    if (status != CL_SUCCESS)
    {
        scl->cl_errcode = status;
        sprintf(scl->error, "FAIL scl_buffer_create_return_errcode. Failed to create buffer.\n");
        return SCL_OPENCL_ERROR;
    }
    *buffer_ptr = buffer;
    return SCL_SUCCESS;
}

void scl_buffer_free(cl_mem buffer)
{
    clReleaseMemObject(buffer);
}
