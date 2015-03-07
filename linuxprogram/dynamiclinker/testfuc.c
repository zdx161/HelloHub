#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "structfun.h"


int main()
{
    void *handle;
    struct hw_module_t *hmi;
    
    handle = dlopen("libstructfun.so", RTLD_NOW);
    if (handle == NULL) {
        char const *err_str = dlerror();
        printf("load: %s\n", err_str?err_str:"unknown");
        exit(EXIT_FAILURE);
    }

    const char *sym = HAL_MODULE_INFO_SYM_AS_STR;

    hmi = (struct hw_module_t *) dlsym(handle, sym);
    if (hmi == NULL) {
        printf("load: couldn't find symbol %s", sym);
        exit(EXIT_FAILURE);
    }

    printf("return %d\n", hmi->methods->open(3, 4));
    
    dlclose(handle);
    
    return 0;
}
