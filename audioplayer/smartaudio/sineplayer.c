#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <alsa/asoundlib.h>

#define ENABLE_VOLUME
#ifdef ENABLE_VOLUME
#include "volume.h"
#else
typedef unsigned int uint32_t;
#endif
typedef unsigned char uchar_t;

typedef struct {
    uint32_t rate;
    uint32_t channels;
    uint32_t period_size;
    uint32_t period_count;
    snd_pcm_format_t format;
    snd_pcm_stream_t stream;
} pcm_config_t;

pcm_config_t pcmconfig = {
    .rate = 48000,
    .channels = 2,
    .period_size = 8192,
    .period_count = 2,
    .format = SND_PCM_FORMAT_S16_LE,
    .stream = SND_PCM_STREAM_PLAYBACK,
};



void * pcm_open(const int card, const int device, const pcm_config_t *pcmconfig)
{
    snd_pcm_t * pcm_handle = NULL;
    snd_pcm_hw_params_t * hwparams;
    snd_pcm_stream_t stream;
    snd_pcm_uframes_t periodsize;

    char pcm_name[64] = {0};
    int exact_rate;
    int periods;
    int dir;

    stream = pcmconfig->stream;
    snprintf(pcm_name, sizeof(pcm_name), "plughw:%d,%d", card, device);


    /* Allocate the snd_pcm_hw_params_t structure on the stack.*/
    snd_pcm_hw_params_alloca(&hwparams);

    if(snd_pcm_open(&pcm_handle, pcm_name, stream, 0) < 0){
        fprintf(stderr, "Error opening PCM device %s\n", pcm_name);
        return NULL;
    }

    if(snd_pcm_hw_params_any(pcm_handle, hwparams) < 0){
        fprintf(stderr, "Can not configure this PCM device.\n");
        return NULL;
    }

    periods = pcmconfig->period_count;
    periodsize = pcmconfig->period_size;

    if(snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0){
        fprintf(stderr, "Error setting access.\n");
        return NULL;
    }

    /* Set sample format */
    if(snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE) < 0){
        fprintf(stderr, "Error setting format.\n");
        return NULL;
    }

    /* Set sample rate. If the exact rate is not supported by the hardware, use nearest possbile rate. */
    exact_rate = pcmconfig->rate;

    if(snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &exact_rate, 0) < 0){
        fprintf(stderr, "Error setting rate.\n");
        return NULL;
    }
    if(pcmconfig->rate != exact_rate){
        fprintf(stderr, "The rate %d HZ is not supported by your hardware.\n ==> Using %d HZ instead.\n", pcmconfig->rate, exact_rate);
    }

    /* Set number of channels */
    if(snd_pcm_hw_params_set_channels(pcm_handle, hwparams, 2) < 0){
        fprintf(stderr, "Error setting channels. \n");
        return NULL;
    }

    /* Set number of periods. Periods used to be called fragments. */
    if(snd_pcm_hw_params_set_periods(pcm_handle, hwparams, periods, 0) < 0){
        fprintf(stderr, "Error setting periods.\n");
        return NULL;
    }

    if(snd_pcm_hw_params_set_buffer_size(pcm_handle, hwparams, (periodsize * periods) >> 2) < 0){
        fprintf(stderr, "Error setting buffersize.\n");
        return NULL;
    }

    if(snd_pcm_hw_params(pcm_handle, hwparams) < 0){
        fprintf(stderr, "Error setting HW params. \n");
        return NULL;
    }

    return pcm_handle;
}

void pcm_close(void * pcm_handle)
{
    if (pcm_handle != NULL) {
        /* Stop PCM device and drop pending frames */
        snd_pcm_drop(pcm_handle);

        /* Stop PCM device after pending frames have been played */
        snd_pcm_drain(pcm_handle);
    }
}

#ifdef ENABLE_VOLUME
int pcm_sine(void * pcm_handle, uchar_t * data, int frames)
{
    int freq = 440;
    double max_phase = 2. * M_PI; 
    double step = max_phase * freq / (double) 48000;
    const uint32_t maxval = (1 << 15) -1;
    double phase = 0;
    short *pcm_buffer = NULL;
    Volume vol;

    int pcmreturn, l1, l2, l3;
    int num_frames = 1024 * 2;
    int volidx = 0;

    for (l1 = 0; l1 < 32; l1++) {
        float ampl = computeamplification(volidx);
        vol = applyvolume(ampl);
        printf("L: amplification->%f, volL->%d, decibel->%f\n", ampl, vol.volL, 20*log10(((double)((maxval*vol.volL)>>12))/(double)maxval));
        printf("R: amplification->%f, volR->%d, decidel->%f\n", ampl, vol.volR, 20*log10(((double)((maxval*vol.volR)>>12))/(double)maxval));

        for (l3 = 0; l3 < 24; l3 ++){
            pcm_buffer = (short *)data;
            for (l2 = 0; l2 < num_frames; l2 ++) {
                int dpcm = maxval * sin(phase);
                int pcm = mulRL(1, (uint32_t)dpcm, vol.volL);
                *pcm_buffer++ = (pcm >> 12) & 0xFFFF;
                pcm = mulRL(0, (uint32_t)dpcm, vol.volR);
                *pcm_buffer++ = (pcm >> 12) & 0xFFFF;
                phase += step;
            }

            while((pcmreturn = snd_pcm_writei(pcm_handle, data, frames)) < 0){
                snd_pcm_prepare(pcm_handle);
                fprintf(stderr, "<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>");
            }
        }

        volidx = (volidx ++) % 16;
    }
}
#endif

int pcm_write(void * pcm_handle, uchar_t *data, int frames)
{
    int pcmreturn, l1, l2;
    short s1, s2;
    int num_frames = 1024;

    for(l1 = 0; l1 < 100; l1++){
        for(l2 = 0; l2 < num_frames; l2++){
            s1 = (l2 % 128) * 100 - 5000;
            s2 = (l2 % 256) * 100 - 5000;
            data[4*l2] = (unsigned char)s1;
            data[4*l2+1] = s1 >> 8;
            data[4*l2+2] = (unsigned char)s2;
            data[4*l2+3] = s2 >> 8;
        }
        while((pcmreturn = snd_pcm_writei(pcm_handle, data, frames)) < 0){
            snd_pcm_prepare(pcm_handle);
            fprintf(stderr, "<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>");
        }
    }

    return pcmreturn;
}

#define TEST_SINE_PLAYER
#ifdef TEST_SINE_PLAYER

int main()
{
    uchar_t *data = NULL;
    int frames = 0;
    int card = 0;
    int device = 0;
    const int periodsize = 8192;
    snd_pcm_t *pcm_handle = NULL;

    data = (uchar_t *)calloc(1, periodsize);
    frames = periodsize >> 2;

    pcm_handle = pcm_open(card, device, &pcmconfig);

    if (pcm_handle == NULL) {
        printf("pcm open failed. \n");
        exit(EXIT_FAILURE);
    }

#ifdef ENABLE_VOLUME
    pcm_sine(pcm_handle, data, frames);
#else
    pcm_write(pcm_handle, data, frames);
#endif

    pcm_close(pcm_handle);

    free(data);

    return 0;
}



#endif
