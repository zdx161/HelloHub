#include <stdio.h>
#include <stdlib.h>

void bitshow1(unsigned int a)
{
    if (a & 0xFFFFFFFF) {
        printf("%d ", a & 0x1);
        return bitshow1(a >> 1);
    }

    printf("\n");
}

void bitshow2(int a)
{
    unsigned int bit = 1 << (sizeof(a) * 8 - 1);
    printf("%d\n", bit);
    for (; bit & ((unsigned int)(~0)); bit = bit >> 1)
        printf("%d ", (bit & (unsigned int)a) > 0);
    printf("\n");
}

void swap(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
    printf("a:%d, b: %d\n", *a, *b);
}

int main()
{
    bitshow1(0xF010);
    bitshow2(8);
    int a = 10, b = 20;
    printf("a:10(%d), b:20(%d)\n", a, (swap(&a, &b), b));
    int x = (a, b);
    printf("x:%d\n", x);

    return 0;
}
