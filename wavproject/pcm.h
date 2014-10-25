#ifndef PCM_HEADER_H
#define PCM_HEADER_H
#include "common.h"

void generate_sine(int offset, int count, double *_phase, int freq, AudioInfo info, uchar *pcm);

#endif
