#ifndef COMPLEX_FUNCTION_H
#define COMPLEX_FUNCTION_H

//Region of redefine type of data
typedef struct {
    double real;
    double imag;
} complex;

//complex operation for marco replace
//inline for C++, but marco for c


//complex operation for calling function
void swap_complex(complex *c1, complex *c2);

complex addition_complex(complex c1, complex c2);
complex subtract_complex(complex c1, complex c2);
complex multiply_complex(complex c1, complex c2);
complex num_mul_complex(complex c1, double i2);
complex division_complex(complex c1, complex c2);

#endif
