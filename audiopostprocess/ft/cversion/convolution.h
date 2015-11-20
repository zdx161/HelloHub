#ifndef CONVOLUTION_FUNCTION_H
#define CONVOLUTION_FUNCTION_H

//from Using the GNU Compiler Collection p. 307
#define PRINT(fmt, ...)  printf("[%s,%d]"fmt"\n", __func__, __LINE__, ## __VA_ARGS__)
#define SWAP(a, b) double t; t = a; a = b; b = t
#define SUBPOW(a) (a * a)

typedef struct {
    int size;
    double * sample;
} SIGNAL;

typedef struct {
    int size;
    int * num;
} HTG;

typedef struct {
    int max;
    int min;
} EXTREMUM;

SIGNAL * convolution_input(SIGNAL * x, SIGNAL * h);
SIGNAL * convolution_output(SIGNAL * x, SIGNAL * h);
SIGNAL * correlation(SIGNAL * a, SIGNAL * b);
SIGNAL * difference(SIGNAL * x);
SIGNAL * sum(SIGNAL * x);

#endif
