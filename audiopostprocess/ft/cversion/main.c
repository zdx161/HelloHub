#include "common.h"
#include <stdio.h>

int main()
{
    double data[8][2] = {0};

    printarray((double *)data, 2, 8, 2);

    return 0;
}
