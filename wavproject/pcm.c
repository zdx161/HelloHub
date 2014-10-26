#include <stdio.h>
#include <math.h>
#include "pcm.h"

void generate_sine(int offset, int count, double *_phase, int freq, AudioInfo info, uchar *pcm)
{
    int channels = info.channels;
    int format_bits = info.bps;
    int rate = info.rate;
    static double max_phase = 2. * M_PI;
    double phase = *_phase;
    double step = max_phase*freq/(double)rate;
    //unsigned char *samples[channels];
    uchar *samples = pcm;
    int steps[channels];
    unsigned int chn;
    //int format_bits = snd_pcm_format_width(format);
    printf("format_bits:%d\n", format_bits);
    unsigned int maxval = (1 << (format_bits - info.decibel - 1)) - 1;
    printf("maxval:%u\n", maxval);
    int bps = format_bits / 8;  /* bytes per sample */
    int phys_bps = 16 / 8;
    int big_endian = 0;
    int to_unsigned = 0;
    int is_float = 0;
#if 0
    FILE *fp=NULL;
    fp = fopen("dumppcm", "a+");
    if(fp == NULL)
        printf("open dump file failed.\n");
#endif

    /* verify and prepare the contents of areas */
    for (chn = 0; chn < channels; chn++) {

        //samples[chn] = ((uchar *)areas[chn].addr) + (areas[chn].first / 8);

        steps[chn] = format_bits / 8;
        //samples[chn] += offset * steps[chn];
    }

    /* fill the channel areas */
    while (count-- > 0) {
        union {
            float f;
            int i;
        } fval;

        int res, i;

        if (is_float) {
            fval.f = sin(phase) * maxval;
            res = fval.i;
        } else
            res = sin(phase) * maxval;

        if (to_unsigned)
            res ^= 1U << (format_bits - 1);
        for (chn = 0; chn < channels; chn++) {
            /* Generate data in native endian format */
            if (big_endian) {
                for (i = 0; i < bps; i++)
                    ;//*(samples[chn] + phys_bps - 1 - i) = (res >> i * 8) & 0xff;
            } else {
                for (i = 0; i < bps; i++){
                    //*(samples[chn] + i) = (res >>  i * 8) & 0xff;
                    *(samples + i) = (res >>  i * 8) & 0xff;
#if 0                    
                    unsigned char sample =  (res >>  i * 8) & 0xff;
                    if(i == 0)
                        sample = 0;
                    //*(samples[chn] + i) = 0;
                    if(fp != NULL){
                        fwrite((char*)(&sample/*samples[chn] + i*/), 1, 1,fp);
                    }
#endif
                }
            }
            //samples[chn] += steps[chn];
            samples += steps[chn];
        }

        phase += step;
        if (phase >= max_phase)
            phase -= max_phase;
    }

    *_phase = phase;
#if 0
    if(fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
#endif
}
