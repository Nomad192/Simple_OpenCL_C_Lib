#include "scl_tools.h"

#include <stdio.h>

void scl_print_error(SCL *scl) {
    fprintf(stderr, "%s\n", scl->error);
}
