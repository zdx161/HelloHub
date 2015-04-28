#include <stdio.h>
#include <math.h>

int main()
{
    //log = loge == ln != log10 != log2
    printf("decibel:%f\n", 20 * log(((double)12)/((double)2047)));
    printf("decibel:%f\n", 20 * log(((double)1)/((double)3)));
    printf("decibel:%f\n", 20 * log2((double)0.5));
    printf("decibel:%f\n", 20 * log(((double)1)/((double)4097)));

    printf("0x%x\n", 1 ^ 0); //^ = XOR
    printf("0x%x, 0x%x\n", -1, -1 >> 31);
    printf("0x%x, 0x%x\n", 1, 1 >> 31);

    return 0;
}

