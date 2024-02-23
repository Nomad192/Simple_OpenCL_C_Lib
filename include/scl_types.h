#ifndef SIMPLE_OPENCL_C_LIB__SCL_TYPES_H
#define SIMPLE_OPENCL_C_LIB__SCL_TYPES_H

#include <inttypes.h>

typedef int32_t scl_status;
#define INIT_ST_SP PRId32
typedef uint32_t scl_number;
#define INIT_NUM_SP PRIu32

/* Error Codes */
#define SCL_SUCCESS     (0) // SCL_SUCCESS
#define DEFAULT_ERROR   (7)

#endif //SIMPLE_OPENCL_C_LIB__SCL_TYPES_H
