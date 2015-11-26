#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <wchar.h>
#include <errno.h>


int main()
{
    char i;
    char * ptr = NULL;
    char * ptr1 = NULL;
    char * tmp = NULL;

    ptr = (char *)malloc(64);
    if (ptr == NULL) {
        printf("malloc failed.\n");
        exit(EXIT_FAILURE);
    }

    ptr1 = (char *)malloc(512 + 9);
    if (ptr1 == NULL) {
        printf("error:%s\n", strerror(errno));
    } else {
        printf("addr1: %p\n", ptr1);
        printf("addr1 - addr: 0x%lx\n", ptr1 - ptr);
        for (tmp = ptr + 64; tmp < ptr1; tmp++) {
            printf("0x%x ", *tmp);
        }

        printf("\n");

        free(ptr1);
        ptr1 = NULL;
    }

    //0x51 = 5 * 16 + 1 = 4 * 16 + 16 + 1 = 64 + 17
    //hex round(0: hex <= 8; 1:hex > 8)
    printf("addr: %p\n", ptr);

    for(i = 16; i > 0; i--){
        printf("0x%x ", *((char*)(ptr-i)));
    }

    printf("\n");
    free(ptr);

    //test stack size
    //ulimit: stack size 8192 kbytes

    //int STACKSIZE = 8192 * 1024;
    //char stack_size[STACKSIZE];

    //segmentation fault
    //stack overflow

    //stack_size[0] = 'a';
    //printf("test\n");

    char c[32] = {0};
    memset(c, 41, 32);

    for (i = 0; i < 32; i++) {
        printf("%c ", c[i]);
    }

    printf("\n");

    int data[32] = {0};

    wmemset(data, INT_MAX -1, 32);

    for (i = 0; i < 32; i++) {
        printf("%d ", data[i]);
    }

    printf("\n");
    printf("%ld\n", sizeof(wchar_t));

    return 0;
}
