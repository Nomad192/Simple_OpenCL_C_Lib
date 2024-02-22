#include "scl_init.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "scl_platform.h"
#include "scl_device.h"

SCL *create() {
    SCL *scl = (SCL *) malloc(sizeof(SCL));

    if (scl != NULL) {
        scl->platform_number = -1;
        scl->device_number = -1;

        scl->num_platforms = -1;
        scl->platforms = NULL;
        scl->platform_name = NULL;
        scl->platform_id = NULL;

        scl->num_devices = -1;
        scl->devices = NULL;
        scl->device_name = NULL;
        scl->device_id = NULL;

        scl->error = (char *) malloc(sizeof(char) * 1000);
    }

    return scl;
}

scl_status init(SCL *scl, scl_number target_platform_number, scl_number target_device_number) {
    CHECK(get_platform_id(scl, target_platform_number))
    CHECK(get_platform_name(scl))
    CHECK(get_device_id(scl, target_device_number))
    CHECK(get_device_name(scl))

    return SCL_SUCCESS;
}

void scl_print_error(SCL *scl) {
    fprintf(stderr, "%s\n", scl->error);
}

void scl_free(SCL *scl) {
    free(scl->error);
    free(scl->devices);
    free(scl->device_name);
    free(scl->platforms);
    free(scl->platform_name);
    free(scl);
}
