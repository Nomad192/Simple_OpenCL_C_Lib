#include "scl_tools.h"

#include <stdio.h>
#include <inttypes.h>

char *scl_get_source(SCL *scl, size_t i) {
    return *(char **) vector_get(scl->sources, i);
}

void scl_print_error(SCL *scl) {
    fprintf(stderr, "cl_errcode: %" PRIi32 "\n%s\n", scl->cl_errcode, scl->error);
}
