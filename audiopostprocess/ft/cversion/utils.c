#include "common.h"
#include <stdio.h>
#include <stdarg.h>

void printarray(double *array, char c, int dim, ...)
{
    va_list ap;
    int i, size = 1;

    va_start(ap, dim);

    while (dim--) {
        size *= va_arg(ap, int);
    }

    va_end(ap);


    if (size <= 0 || !array)
        return;

    for (i = 0; i < size; i++) {
        if (c == 'i') {
            if (*(array + i + 1) >= 0.0)
                printf("%lf+%lfi\t", *(i + array), *(i + 1 + array));
            else
                printf("%lf%lfi\t", *(i + array), *(i + 1 + array));
            i++;
        }
        else
            printf("%lf\t", *(array + i));

        if ((i + 1 ) % 16 == 0)
            printf("\n");
    }

    if (i % 16 != 0)
        printf("\n");
}
