#include <stdio.h>

#ifdef USE_SECOND_WAY
#include "simplemath.h"
#else
#include <stdlib.h>
#include <dlfcn.h>

#define funtostr(fun) #fun
#endif

int main()
{
#ifdef USE_SECOND_WAY 
    printf("1 + 7 = %d\n", add(1, 7));

#else
    void *handle = NULL;
    char *err;
    int (*add)(int, int); 
    handle = dlopen("libsimplemath.so", RTLD_LAZY);
    err = dlerror();
    if (!handle) {
        printf("dlopen err: %s\n", err);
        exit(EXIT_FAILURE);
    }

    add = dlsym(handle, funtostr(add));
    err = dlerror();
    if (err) {
        printf("dlsym err: %s\n", err);
        exit(EXIT_FAILURE);
    }

    printf("3 + 5 = %d\n", add(3, 5));

    dlclose(handle);
#endif

    return 0;
}
