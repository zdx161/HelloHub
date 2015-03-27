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
    printf("addr: 0x%x\n", ptr);
    
    for(i = 16; i > 0; i--){
        printf("0x%x ", *((char*)(ptr-i)));
    }

    printf("\n");
    free(ptr);

    return 0;
}
