#include <stdio.h>
#include <stdlib.h>
#include "extern.h"
int test = 0;

int main()
{
    printf("test: %d\n", test);
    test = 1;
    printf("test: %d\n", test);
    setvalue();
    printf("test: %d\n", test);

    return 0;
}
