#include <stdio.h>
#include <math.h>

#include "sampling.h"



//2 + 3 * cos((double)2*PI*50*t-(double)PI*30/((double)180))  + 1.5*cos((double)2*PI*75*t+(double)PI*90/((double) 180));
double signalfunc(double t)
{
    double value;
    value = DC(2) + COSINE(3, 50, t, -30) + COSINE(1.5, 75, t, 90);
    return 0;
}

Bbool sampling(SigFun sf, int f, Matrix * sample)
{
    double t;
    complex * sele;
    double period = 1 / ((double)f);

    sele = sample->element;
    for (t = 0.0; t < 1.0; t += period) {
        sele->real = sf(t);
    }
}
