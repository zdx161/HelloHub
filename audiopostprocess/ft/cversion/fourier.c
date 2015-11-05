#include <stdio.h>
#include <math.h>

#include "fourier.h"

Bool Fourierphase(Matrix * fourier, Matrix * phase)
{
    amplitude = sqrt(pow(((*ptr)[i][0]), 2) + pow(((*ptr)[i][1]), 2));
}

//DFT: e^(-j*2*pi*n*k/N)
Bool fouriercoeff(Matrix * coeff)
{
    int k, m, row, col;
    complex * ele;
    double w;

    if ((coeff == NULL) || (coeff->element == NULL)) {
        printf("error: there is not memory in Matrix.\n");
        return False;
    }

    row = coeff->row;
    col = coeff->col;
    ele = coeff->element;

    for (k = 0; k < row; k++) {
        for (m = 0; m < col; m++, ele++) {
            w = (double)(2 * PI * m * k) / ((double) row);
            ele->real =  cos(w);
            ele->imag =  sin(w);
        }
    }

    return True;
}
