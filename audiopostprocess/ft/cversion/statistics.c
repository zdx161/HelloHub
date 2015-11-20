#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include "convolution.h"

double mean(SIGNAL * s)
{
    int size, i;
    double *samp, sum = 0.;

    size = s->size;
    samp = s->sample;

    for (i = 0; i < size; i++) {
        sum += samp[i];
    }

    return sum / ((double)size);
}

//standard deviation
double sdeviation(SIGNAL * s)
{
    int size, i;
    double *samp, m, sum = 0;

    size = s->size;
    samp = s->sample;
    m = mean(s);

    for (i = 0; i < size; i++) {
        sum += SUBPOW(samp[i] - m);
    }

    return sum / ((double) (size - 1));
}

double rdeviation(SIGNAL * s)
{
    int size, i;
    double *samp, mean = 0, sum = 0;

    size = s->size;
    samp = s->sample;

    for (i = 0; i < size; i++) {
        sum += samp[i];
    }

    mean = SUBPOW(sum);
    mean = mean / ((double)size);

    for (i = 0; i < size; i++) {
        sum += SUBPOW(samp[i]) ;
    }

    return (sum - mean) / ((double) (size - 1));
}

EXTREMUM max(SIGNAL * s)
{
    double max = 0., min = 0.;
    EXTREMUM em;
    int i, size;
    double *samp;

    size = s->size;
    samp = s->sample;

    for (i = 0; i < size; i++) {
        if (samp[i] > max)
            max = samp[i];
        else if (samp[i] < min)
            min = samp[i];
    }

    em.max = max;
    em.min = min;

    return em;
}

HTG * histogram(SIGNAL * s)
{
    EXTREMUM em;
    HTG * htg = NULL;
    double mx, mn, size;
    double *samp;
    int * num;
    int i, ss, index;

    em = max(s);
    mx = ceil(em.max);
    mn = floor(em.min);
    size = mx - mn;
    htg = (HTG *) calloc(1, (size_t)(sizeof(HTG) + size * sizeof(int)));

    if (!htg) {
        PRINT("error: %s", strerror(errno));
        return htg;
    }

    htg->num = (int *)&htg[1];
    num = htg->num;
    ss = s->size;
    samp = s->sample;

    for (i = 0; i < ss; i++) {
        index = (int)(floor(samp[i]));
        index = index < 0 ? index + (0 - mn) : index;
        num[index]++;
    }

    return htg;;
}
