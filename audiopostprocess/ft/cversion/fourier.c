#include <stdio.h>
#include <math.h>

#include "fourier.h"

Bool fourieramplitude(Matrix * fourier, Matrix * amplitude)
{
    int r, c, row, col;
    complex *fele, *aele;

    if (fourier == NULL ||  amplitude == NULL) {
        printf("error: Matrix can not be NULL.\n");
        return False;
    }

    if (fourier->element == NULL || amplitude->element == NULL) {
        printf("error: there is not memory in element of Matrix\n");
        return False;
    }

    if (!((fourier->row == amplitude->row) && (fourier->col == amplitude->col))) {
        printf("error: the attribute of Matrix can not be match\n");
        return False;
    }

    row = fourier->row;
    col = fourier->col;
    fele = fourier->element;
    aele = amplitude->element;

    for (r = 0; r < row; r++) {
        for (c = 0; c < col; c++, fele++, aele++) {
            aele->real = sqrt(POWER(fele->real) + POWER(fele->imag));
            aele->imag = 0;
        }
    }

    return True;
}

Bool signalamplitude(Matrix * fam, Matrix * sam)
{
    int r, c, row, col;
    complex *fele, *sele;

    if (fam == NULL ||  sam == NULL) {
        printf("error: Matrix can not be NULL.\n");
        return False;
    }

    if (fam->element == NULL || sam->element == NULL) {
        printf("error: there is not memory in element of Matrix\n");
        return False;
    }

    if (!((fam->row == sam->row) && (fam->col == sam->col))) {
        printf("error: the attribute of Matrix can not be match\n");
        return False;
    }

    row = fam->row;
    col = fam->col;
    fele = fam->element;
    sele = sam->element;

    for (r = 0; r < row; r++) {
        for (c = 0; c < col; c++, fele++, sele++) {
            sele->real = fele->real / row * 2;
        }
    }

    sam->element->real /= 2;

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
            w = -(double)(2. * PI * m * k) / ((double) col);
            ele->real =  cos(w);
            ele->imag =  sin(w);
        }
    }

    return True;
}

Bool fouriercoeff_i(Matrix * coeff)
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
            w = (double)(2. * PI * m * k) / ((double) col);
            ele->real =  cos(w);
            ele->imag =  sin(w);
        }
    }

    return True;
}
