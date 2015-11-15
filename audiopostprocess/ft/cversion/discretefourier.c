#include "stdio.h"
#include "fourier.h"

Matrix * dft(Matrix * sig)
{
    Matrix * coeff;
    Matrix * tmatrix;

    if (sig == NULL || sig->row <= 0 || sig->element == NULL)
    {
        printf("error: There are some errors in Matrix.\n");
        return NULL;
    }

    coeff = allocate_matrix(sig->row, sig->row);
    tmatrix = allocate_matrix(sig->row, sig->col);

    fouriercoeff(coeff);
    //print_matrix(coeff);

    multiply_matrix(coeff, sig, tmatrix);

    free_matrix(coeff);

    return tmatrix;
}
