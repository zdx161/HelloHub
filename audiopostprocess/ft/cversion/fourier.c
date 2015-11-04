#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"

#define PI 3.14159267
#define DIM 256//512//256//8

typedef double (*THRDIM)[DIM][2];

//DFT: e^(-j*2*pi*n*k/N)
void createcoeff(double (*p)[DIM][2], int size)
{
    int k, n;
    double w;

    for (k = 0; k < size; k++) {
        for (n = 0; n < size; n++) {
            w = (double)(2 * PI * n * k) / ((double) size);
            (*p)[n][0] = cos(w);
            (*p)[n][1] = sin(w);
        }
        p++;
    }
}

THRDIM opendft(double (*p)[DIM][2], double *data, int size)
{
    int k, n;
    THRDIM fdata = NULL;

    fdata = (THRDIM)calloc(1, DIM * 2 * sizeof(double));
    if (!fdata) {
        printf("error: allocate memory failed.\n");
        return NULL;
    }

    for (k = 0; k < size; k++) {
        for (n = 0; n < size; n++) {
            (*fdata)[k][0] += data[n] * p[k][n][0];
            (*fdata)[k][1] += data[n] * p[k][n][1];
        }
    }

    return fdata;
}

void closedft(THRDIM td)
{
    if (td)
        free(td);
}

int main()
{
    double coeff[DIM][DIM][2] = {0};
    double data[DIM] = {0.0};
    THRDIM ptr;

    createcoeff(coeff, DIM);
    resample(DIM, data);
    ptr = dft(coeff, data, DIM);

    int i, j, line;

    printf("=======================fourier coeff===============================\n");
    printarray((double*) coeff, 'i', 3, DIM, DIM, 2);

    printf("=============================DFT==================================\n");
    printarray((double*) ptr, 'i', 2, DIM, 2);

    if (ptr)
        free(ptr);

    return 0;
}

void phase()
{
    double amplitude = sqrt(pow(((*ptr)[i][0]), 2) + pow(((*ptr)[i][1]), 2));
    printf("%lf\t", i == 0 ? amplitude / DIM : amplitude * 2 / DIM);
}
