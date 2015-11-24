#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <wchar.h>


int main()
{
    char i;
    char *ptr = (char *)malloc(64);
    if(ptr == NULL){
        printf("malloc failed.\n");
        exit(EXIT_FAILURE);
    }

    //0x51 = 5 * 16 + 1 = 81 = 64 + 17
    printf("addr: 0x%x\n", ptr);

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
