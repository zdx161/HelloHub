/*************************************************************************
 * A square wave is a non-sinusoidal periodic waveform (which can
 * be represented as an infinite summation of sinusoidal waves),
 * in which the amplitude alternates at a steady frequency between
 * fixed minimum and maximum values, with the same duration at
 * minimum and maximum. The transition between minimum to maximum
 * is instantaneous for an ideal square wave; this is not realizable
 * in physical systems. Square waves are often encountered in
 * electronics and signal processing.
 * link:https://en.wikipedia.org/wiki/Square_wave
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define PI (3.14159265359)


double sampling_square(int n, int f, double t)
{
    int i;
    double w = 0;
    double sum = 0;

    w = 2 * PI * f * t;

    for (i = 0; i < n; i++) {
        sum += sin(w * (2 * i + 1)) / ((double)(2 * i + 1));
    }

    return sum * ((double)4 / PI);
}


double sampling_triangle(int n, int f, double t)
{
    int i;
    double w = 0;
    double sum = 0;

    w = 2 * PI * f * t;

    for (i = 0; i < n; i++) {
        if (i % 2 == 0)
            sum += sin(w * (2 * i + 1)) / (double)(2 * i + 1) / (double)(2 * i + 1);
        else
            sum -= sin(w * (2 * i + 1)) / (double)(2 * i + 1) / (double)(2 * i + 1);
    }

    return ((double)8 / PI / PI) * sum;
}


double sampling_sawtooth(int n, int f, double t)
{
    int i;
    double w = 0;
    double sum = 0;

    w = 2 * PI * f * t;

    for (i = 1; i <= n; i++) {
        sum += sin(w * i) / (double)i;
    }

    return ((double)1 / 2) - (((double)1 / PI) * sum);
}
