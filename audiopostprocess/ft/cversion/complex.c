#include <stdio.h>
#include "complex.h"

complex addition_complex(complex c1, complex c2)
{
    complex local;

    local.real = c1.real + c2.real;
    local.imag = c1.imag + c2.imag;

    return local;
}


complex subtract_complex(complex c1, complex c2)
{
    complex local;

    local.real = c1.real - c2.real;
    local.imag = c1.imag - c2.imag;

    return local;
}

complex multiply_complex(complex c1, complex c2)
{
    complex local;

    local.real = c1.real * c2.real - c1.imag * c2.imag;
    local.imag = c1.real * c2.imag + c1.imag * c2.real;

    return local;
}


complex division_complex(complex c1, complex c2)
{
    complex local = {0};
    double denominator;

    if (c2.real == 0 && c2.imag == 0) {
        printf("error: complex c2 can not be (complex)zero.\n");
        return local;
    }

    denominator = c2.real * c2.real + c2.imag * c2.imag;
    local.real = (c1.real * c2.real + c1.imag * c2.imag) / denominator;
    local.imag = (c1.imag * c2.real - c1.real * c2.imag) / denominator;

    return local;
}
