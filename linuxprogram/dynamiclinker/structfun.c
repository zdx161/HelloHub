#include <stdio.h>
#include <stdlib.h>
#include "structfun.h"

#define MAKE_TAG(A, B, C, D) ((A << 24) | (B << 16) | (C << 8) | D)
#define MODULE_TAG MAKE_TAG('T','E','S','T')

static int legacy_fun_module(int a, int b)
{
    return a + b;
}

static struct hw_module_methods_t lagecy_fun_module_methods = {
    open:legacy_fun_module,
};

struct legacy_hw_module HAL_MODULE_INFO_SYM = {
    module: {
        common: {
            tag: MODULE_TAG, 
            version_major: 1,
            version_minor: 0,
            id: "audio_policy",
            name: "audio test",
            author: "zedong_xiong",
            methods: &lagecy_fun_module_methods,
            dso: NULL,
            reserved: {0},
        },
    },
};
