#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

typedef struct AUDIO_INFO{
    int channels;
    int rate;
    int bps;
    int decibel;
    //int period_time;
} AudioInfo;

typedef unsigned char uchar;

int alocate_buffer(uchar **pcm, int size);
void free_buffer(uchar **pcm);

#endif
