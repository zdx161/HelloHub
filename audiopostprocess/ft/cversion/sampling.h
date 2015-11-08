#ifndef SAMPLING_FUNCTION_H
#define SAMPLING_FUNCTION_H

#include "matrix.h"


//phase = omega * x + phi
//initial phase = phi (x = 0)
//Amplitude
#define SINE(am, f, t, an) (am * sin(PHASE(f, t, an)))
#define COSINE(am, f, t, an)  (am * cos(PHASE(f, t, an)))

typedef double (*SigFun)(double);


Bool sampling(SigFun sf, int hz, Matrix * sample);

#endif
