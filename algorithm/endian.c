#include <stdio.h>


int main()
{
    short data = 0x1234;
    char *ptr;
    ptr =(char*)(&data);
    if(ptr[0] == 0x34)
        printf("little endian\n");
    else
        printf("big endian\n");

    return 0;
}
