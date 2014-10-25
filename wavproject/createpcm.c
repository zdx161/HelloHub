#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wav.h"

static void generate_sine(int offset, int count, double *_phase, int channels,
                          int freq, int format_bits, int rate)
{
    static double max_phase = 2. * M_PI;
    double phase = *_phase;
    double step = max_phase*freq/(double)rate;
    //unsigned char *samples[channels];
    int steps[channels];
    unsigned int chn;
    //int format_bits = snd_pcm_format_width(format);
    printf("format_bits:%d\n", format_bits);
    unsigned int maxval = (1 << (format_bits - 1 - 1)) - 1;
    printf("maxval:%u\n", maxval);
    int bps = format_bits / 8;  /* bytes per sample */
    int phys_bps = /*snd_pcm_format_physical_width(format)*/ 16 / 8;
    int big_endian = 0;//snd_pcm_format_big_endian(format) == 1;
    int to_unsigned = 0;//snd_pcm_format_unsigned(format) == 1;
    int is_float = 0;/*(format == SND_PCM_FORMAT_FLOAT_LE ||
                        format == SND_PCM_FORMAT_FLOAT_BE);*/
    FILE *fp=NULL;
    fp = fopen("dumppcm", "a+");
    if(fp == NULL)
        printf("open dump file failed.\n");
    
    /* verify and prepare the contents of areas */
    for (chn = 0; chn < channels; chn++) {
        /*
        if ((areas[chn].first % 8) != 0) {
            printf("areas[%i].first == %i, aborting...\n", chn, areas[chn].first);
            exit(EXIT_FAILURE);
        }*/
        
        //samples[chn] = /*(signed short *)*/(((unsigned char *)areas[chn].addr) + (areas[chn].first / 8));
        
        /*
        if ((areas[chn].step % 16) != 0) {
            printf("areas[%i].step == %i, aborting...\n", chn, areas[chn].step);
            exit(EXIT_FAILURE);
        }*/
                        
        steps[chn] = /*areas[chn].step*/ 16 / 8;
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
                    unsigned char sample =  (res >>  i * 8) & 0xff;
                    if(i == 0)
                        sample = 0;
                    //*(samples[chn] + i) = 0;
                    if(fp != NULL){
                        fwrite((char*)(&sample/*samples[chn] + i*/), 1, 1,fp);     
                    } 
                }
            }
            //samples[chn] += steps[chn];
        }
        phase += step;
        if (phase >= max_phase)
            phase -= max_phase;
    }
    
    *_phase = phase;
    
    if(fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
}
