#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

char * px_ipc_name(const char * name)
{
    char * dir, * dst, * stash;

    if ((dst = (char *)malloc(PATH_MAX)) == NULL)
        return NULL;

    if ((dir = getenv("PX_IPC_NAME")) == NULL) {
#ifdef POSIX_IPC_PREFIX
        dir = POSIX_IPC_PREFIX;
#else
        dir = "/tmp/";
#endif
    }

    stash = (dir[strlen(dir) - 1] == '/') ? "":"/";
    snprintf(dst, PATH_MAX, "%s%s%s", dir, stash, name);

    return (dst);
}
