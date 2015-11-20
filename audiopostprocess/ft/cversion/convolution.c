#include <stdio.h>
#include <stdlib.h>
#include "convolution.h"


SIGNAL * convolution_input(SIGNAL * x, SIGNAL * h)
{
    int i, j, size, xs, hs;
    double * xsamp, * hsamp, * ysamp;
    SIGNAL * y = NULL;

    xs = x->size;
    hs = h->size;
    size = xs + hs - 1;
    y = (SIGNAL *)calloc(1, sizeof(SIGNAL) + size * sizeof(double));

    if (!y) {
        PRINT("error: allocate memory failed for SIGNAL");
        return y;
    }

    y->sample = (double*)&y[1];
    y->size = size;
    xsamp = x->sample;
    hsamp = h->sample;
    ysamp = y->sample;

    for (i = 0; i < xs; i++) {
        for (j = 0; j < hs; j++) {
            ysamp[i + j] += xsamp[i] * hsamp[j];
        }
    }

    return y;
}

SIGNAL * convolution_output(SIGNAL * x, SIGNAL * h)
{
    int i, j, size, xs, hs;
    double * xsamp, * hsamp, * ysamp;
    SIGNAL * y = NULL;

    xs = x->size;
    hs = h->size;
    size = xs + hs - 1;
    y = (SIGNAL *)calloc(1, sizeof(SIGNAL) + size * sizeof(double));

    if (!y) {
        PRINT("error: allocate memory failed for SIGNAL");
        return y;
    }

    y->sample = (double*)&y[1];
    y->size = size;
    xsamp = x->sample;
    hsamp = h->sample;
    ysamp = y->sample;

    for (i = 0; i < size; i++) {
        for (j = 0; j < hs; j++) {
            if ((i >= j) && (i - j < xs))
            ysamp[i] += hsamp[j] * xsamp[i - j];
        }
    }

    return y;
}

SIGNAL * difference(SIGNAL * x)
{
    int xs, i;
    double *xsamp, *ysamp;
    SIGNAL * y = NULL;

    xs = x->size;

    y = (SIGNAL *)calloc(1, sizeof(SIGNAL) + xs * sizeof(double));
    if (!y) {
        PRINT("error: allocate memory failed for SIGNAL");
        return y;
    }

    y->sample = (double *)&y[1];
    y->size = xs;
    xsamp = x->sample;
    ysamp = y->sample;

    for (i = 1; i < xs; i++) {
        ysamp[i] = xsamp[i] - xsamp[i - 1];
    }

    return y;
}


SIGNAL * sum(SIGNAL * x)
{
    int xs, i;
    double *xsamp, *ysamp;
    SIGNAL * y = NULL;

    xs = x->size;

    y = (SIGNAL *)calloc(1, sizeof(SIGNAL) + xs * sizeof(double));
    if (!y) {
        PRINT("error: allocate memory failed for SIGNAL");
        return y;
    }

    y->sample = (double *)&y[1];
    y->size = xs;
    xsamp = x->sample;
    ysamp = y->sample;
    ysamp[0] = xsamp[0];

    for (i = 1; i < xs; i++) {
        ysamp[i] = ysamp[i - 1] + xsamp[i];
    }

    return y;
}

SIGNAL * correlation(SIGNAL * a, SIGNAL * b)
{
    int size, i, half;
    double * bsamp;

    size = b->size;
    bsamp = b->sample;
    half = (size + 1) / 2;

    for (i = 0; i < half; i++) {
        SWAP(bsamp[i], bsamp[size - i - 1]);
    }

    return convolution_output(a, b);
}
