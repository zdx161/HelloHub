#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

typedef struct AUDIO_INFO{
    int channels;
    int rate;
    int bps;
    int decibel;
    int duration;
} AudioInfo;

typedef unsigned char uchar;
typedef unsigned int  uint;

int alocate_buffer(uchar **pcm, int size);
void free_buffer(uchar **pcm);

#endif
