#ifndef STRCUT_FUN_H
#define STRCUT_FUN_H


#define HAL_MODULE_INFO_SYM HMI
#define HAL_MODULE_INFO_SYM_AS_STR "HMI"
struct hw_module_methods_t;
struct hw_module_t;

struct hw_module_t {
    int tag;
    short module_api_version;
#define version_major module_api_version
    short hal_api_version;
#define version_minor hal_api_version
    const char *id;
    const char *name;
    const char *author;
    struct hw_module_methods_t *methods;
    void *dso;
    int reserved[32-7];
};

struct hw_module {
    struct hw_module_t common; 
};

struct legacy_hw_module {
    struct hw_module module;
};

typedef struct hw_module_methods_t {
    int (*open)(int a, int b);
} hw_module_methods_t;

#endif
