#include <stdio.h>
#include <limits.h>
#include <math.h>

static inline short clamp16(int sample)
{
    printf("0x%x ===> 0x%x ^ 0x%x\n", sample, sample >> 15, sample >> 31);
    if ((sample>>15) ^ (sample>>31))
        sample = 0x7FFF ^ (sample>>31);
    return sample;
}

int main()
{
    //log == loge == ln != log10 != log2
    printf("decibel:%f\n", 20 * log10((double)0.5));

    printf("0x%x\n", 1 ^ 0); //^ = XOR

    //signed shift
    printf("0x%x, 0x%x\n", -1, -1 >> 31);
    printf("0x%x, 0x%x\n", 1, 1 >> 31);

    //int 32bit -> short 16bit
    long i;
    printf("%d,0x%x\n", INT_MAX, INT_MAX);
    printf("%d,0x%x\n", INT_MIN, INT_MIN);

#if 0
    //INT_MAX - INT_MIN ===> overflow
    for (i = INT_MIN; i <= INT_MAX; i = i + INT_MAX/32 - INT_MIN/32) {
        printf("%ld\n", clamp16(i));
    }
#else
    for (i = -32768 * 2; i <= 32767 * 2; i = i + 65536/16) {
        printf("%d ----> %d\n", i, clamp16(i));
    }
#endif

    return 0;
}

