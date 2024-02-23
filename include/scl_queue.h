#ifndef SIMPLE_OPENCL_C_LIB__SCL_QUEUE_H
#define SIMPLE_OPENCL_C_LIB__SCL_QUEUE_H

#include <CL/cl.h>

#include "scl_struct.h"
#include "scl_types.h"

scl_status
scl_queue_create_return_errcode(SCL *scl, cl_context context, cl_device_id device_id, cl_command_queue_properties properties,
                                cl_command_queue *command_queue_ptr);

void scl_queue_free(cl_command_queue command_queue);

#endif //SIMPLE_OPENCL_C_LIB__SCL_QUEUE_H
