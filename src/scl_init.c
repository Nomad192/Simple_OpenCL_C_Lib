#include "scl_init.h"

#include <stdlib.h>
#include <stdint.h>

#include "scl_platform.h"
#include "scl_device.h"
#include "scl_tools.h"

SCL *scl_create() {
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

        scl->sources = vec_create(sizeof(char *), 10);

        scl->build_log = NULL;

        scl->error = (char *) malloc(sizeof(char) * 1000);
        scl->cl_errcode = CL_SUCCESS;
    }

    return scl;
}

scl_status scl_init(SCL *scl, scl_number target_platform_number, scl_number target_device_number) {
    CHECK_NO_PRINT(get_platform_id(scl, target_platform_number))
    CHECK_NO_PRINT(get_platform_name(scl))
    CHECK_NO_PRINT(get_device_id(scl, target_device_number))
    CHECK_NO_PRINT(get_device_name(scl))

    return SCL_SUCCESS;
}

void scl_free(SCL *scl) {
    free(scl->error);
    free(scl->devices);
    free(scl->device_name);
    free(scl->platforms);
    free(scl->platform_name);

    clReleaseProgram(scl->program);
    clReleaseContext(scl->context);

    for (size_t i = 0; i < scl->sources->size; ++i)
        free(scl_get_source(scl, i));

    vec_free(scl->sources);

    free(scl);
}
