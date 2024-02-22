#ifndef SIMPLE_OPENCL_C_LIB__SCL_TYPES_H
#define SIMPLE_OPENCL_C_LIB__SCL_TYPES_H

typedef signed int scl_status;
#define INIT_ST_SP "i"
typedef unsigned int scl_number;
#define INIT_NUM_SP "u"

/* Error Codes */
#define SCL_SUCCESS              (0)
#define SCL_ERROR               (-1)
#define SCL_OPENCL_ERROR        (-2)
#define SCL_OUT_OF_MEMORY       (-3)
#define SCL_FILE_NOT_OPEN       (-4)

#endif //SIMPLE_OPENCL_C_LIB__SCL_TYPES_H
