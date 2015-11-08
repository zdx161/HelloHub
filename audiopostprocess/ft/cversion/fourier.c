#include <stdio.h>
#include <math.h>

#include "fourier.h"

Bool fourieramplitude(Matrix * fourier, Matrix * amplitude)
{
    int r, c, row, col;
    complex *fele, *pele;

    if (fourier == NULL ||  phase == NULL) {
        printf("error: Matrix can not be NULL.\n");
        return False;
    }

    if (fourier->element == NULL || phase->element == NULL) {
        printf("error: there is not memory in element of Matrix\n");
        return False;
    }

    if (!((fourier->row == phase->row) && (fourier->col == phase->col))) {
        printf("error: the attribute of Matrix can not be match\n");
        return False;
    }

    row = fourier->row;
    col = fourier->col;
    fele = fourier->element;
    pele = fourier->element;

    for (r = 0; r < row; r++) {
        for (c = 0; c < col; c++, fele++, pele++) {
            pele->real = sqrt(POWER(fele->real) + POWER(fele->imag));
            pele->imag = 0;
        }
    }

    return True;
}

Bool signalamplitude(Matrix * fam, Matrix * sam)
{


    return True;
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
