
#ifndef RIFF_WAV_H
#define RIFF_WAV_H
#include "common.h"

typedef unsigned int DWORD;
typedef unsigned short WORD;

typedef struct {
    DWORD ChunkID;
    DWORD ChunkSize;
    DWORD Format;
} ChuckDes;

typedef struct {
    DWORD Subchunk1ID;
    DWORD Subchunk1Size;
    WORD AudioForamt;
    WORD NumChannles;
    DWORD SampleRate;
    DWORD ByteRate;
    WORD BlockAlign;
    WORD BitsPerSample;
} SubchunkFMT;

typedef struct {
    DWORD Subchunk2ID;
    DWORD Subchunk2Size;
} SubchunkData;


void write_wav_header(void *header, AudioInfo info, int period);
void write_wav(AudioInfo info, uchar *pcm, int size);

#endif
