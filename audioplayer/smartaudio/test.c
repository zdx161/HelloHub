#include <stdio.h>
#include <math.h>

int main()
{
    //log = loge == ln != log10 != log2
    printf("decibel:%f\n", 20 * log(((double)12)/((double)2047)));
    printf("decibel:%f\n", 20 * log(((double)1)/((double)3)));
    printf("decibel:%f\n", 20 * log2((double)0.5));
    printf("decibel:%f\n", 20 * log(((double)1)/((double)4097)));
    return 0;
}

