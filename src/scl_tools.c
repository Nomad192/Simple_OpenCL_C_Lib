#include "scl_tools.h"

#include <stdio.h>
#include <inttypes.h>

void scl_print_error(SCL *scl) {
    fprintf(stderr, "cl_errcode: %" PRIu32 "\n%s\n", scl->cl_errcode, scl->error);
}
