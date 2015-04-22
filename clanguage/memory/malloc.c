#include <stdio.h>
#include <stdlib.h>


int main()
{
    char i;
    char *ptr = (char *)malloc(64);
    if(ptr == NULL){
        printf("malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("addr: %p\n", ptr);
    
    //0x51 = 5 * 16 + 1 = 81 = 64 + 17
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

    return 0;
}
