#ifndef FOURIER_FUNCTION_H
#define FOURIER_FUNCTION_H

#include "matrix.h"

//Macro
#define POWER(x) (x * x)


//Redefine


//Fourier coeff
Bool fourieramplitude(Matrix * Fourier, Matrix * amplitude);
Bool signalamplitude(Matrix * fam, Matrix * sam);
Bool fouriercoeff(Matrix * coeff);

//Discrete-Fourier-Transform
Matrix * dft(Matrix * sig);


//Fast Discrete-Fourier-Transform(Cooley-Tukey's butterfly algorithm)
Bool fft(Matrix * sig);



#endif
