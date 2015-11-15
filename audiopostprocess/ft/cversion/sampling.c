#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#include "sampling.h"



//2 + 3 * cos((double)2*PI*50*t-(double)PI*30/((double)180))  + 1.5*cos((double)2*PI*75*t+(double)PI*90/((double) 180));
double signalfunc(double t)
{
    double value;
    value = DC(2) + COSINE(3, 50, t, -30) + COSINE(1.5, 75, t, 90);
    return value;
}

Bool signalsampling(SigFun sf, int f, Matrix * sample)
{
    double t;
    complex * sele;
    double period = 1 / ((double)f);

    sele = sample->element;
    for (t = 0.0; t < 1.0; t += period, sele++) {
        sele->real = sf(t);
    }
}

Bool pcmsampling(char * path, Matrix * sample)
{
    FILE *fp = NULL;
    int size;
    int r, c, row, col;
    complex * sele;

    if (!path) {
        printf("error: path can not be NULL.\n");
        return False;
    }

    if (sample == NULL || sample->row <=0 || sample->element == NULL) {
        printf("error: there is no memory in Matrix.\n");
        return False;
    }

    errno = 0;
    fp = fopen(path, "r");
    if (!fp) {
        printf("error: can not open path (%s)\n", strerror(errno));
        return False;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    row = sample->row;
    col = sample->col;
    sele = sample->element;

    size = (size > (row * col)) ? (row * col) : size;

    for (r = 0; r < row && size > 0; r++) {
        for (c = 0; (c < col) && (size > 0); c++, sele++, size--) {
            fread((char*)&(sele->real), sizeof(double), 1, fp);
        }
    }

    fclose(fp);

    return True;
}
