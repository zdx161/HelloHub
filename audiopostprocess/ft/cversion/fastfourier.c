#include "fourier.h"


Bool fft(Matrix * sig)
{
    Matrix * coeff;

    if (sig == NULL || sig->row <= 0.0 || sig->element == NULL) {
        printf("error: There are some errors in Matrix.\n");
        return False;
    }

    coeff = allocate_matrix(sig->row / 2, sig->row / 2);

    swap_matrix();

    free_matrix(coeff);


}
