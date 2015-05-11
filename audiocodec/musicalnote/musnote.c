#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PHASE 2. * M_PI
#define RATE 44100
static const NoteHz[7] = {262, 294, 330, 349, 392, 440, 494};


int createpcm(double step, int delay, double *phase, char *out)
{
    int i, j;
    double ph = *phase;
    int maxval = (1 << 15) - 1;
    int num = RATE / delay;
    short * pcm = NULL;
    pcm = (short *) out;

    for (i = 0; i < num; i++) {
        int val = maxval * sin(ph);
        for (j = 0; j < 2; j++) {
            *pcm++ = (short)val; 
        }
        ph += step;
        if (ph >= (MAX_PHASE))
            ph -= (MAX_PHASE);
    }

    *phase = ph;

    return ((char*)pcm) - out;
}

int main()
{
    double step = 0.;
    int delay = 1;
    double phase = 0;
    int size = 0;
    FILE * fp = NULL;
    char *out = NULL;
    int i;

    fp = fopen("note.pcm", "wb");

    if (fp == NULL)
        goto err;

    out = (char *)malloc(44100*2*2);
    if (out == NULL) {
        goto err;
    }

    for (i = 0; i < 7; i++) {
        step = (MAX_PHASE) * NoteHz[i] / (double)RATE;
        size = createpcm(step, delay, &phase, out);
        fwrite(out, 1, size, fp);
    }

err:
    if (fp != NULL) {
        fclose(fp);
        fp = NULL;
    }

    if (out != NULL) {
        free(out);
        out = NULL;
    }

    return 0;
}
