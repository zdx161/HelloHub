/** ************************************************************
 ** Little-endian:store the least significant byte in the
 ** smallest address.
 **
 ** Big-endian system:store the most significant byte of a word
 ** in the smallest address and the least significant byte is
 ** stored in the largest address.
 **
 ** wikipedia link: http://en.wikipedia.org/wiki/Endianness
 ** ***********************************************************/

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
