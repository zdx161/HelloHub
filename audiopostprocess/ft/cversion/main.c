#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>






//for 0 <= k < N/2
//X(k) = E(K) + e^(-2*pi*i*k/N) * O(k)
//X(k+N/2) = E(K) - e^(-2*pi*i*k/N) * O(k)



int main()
{
    /*
    double data[8][2] = {0};
    printarray((double *)data, 2, 8, 2);
    */

    int row, col;
    Matrix * coeff = NULL;

    row = col = 8;

    coeff = allocatematrix(row, col);
    coeffmatrix(coeff);
    printmatrix(coeff);
    freematrix(coeff);

    return 0;
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
