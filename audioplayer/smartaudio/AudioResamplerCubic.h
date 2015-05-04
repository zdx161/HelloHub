#ifndef ANDROID_AUDIO_RESAMPLER_CUBIC_H
#define ANDROID_AUDIO_RESAMPLER_CUBIC_H

#include <stdint.h>
#include <sys/types.h>

typedef int int32_t;
typedef unsigned int uint32_t;

// number of bits used in interpolation multiply - 14 bits avoids overflow
int kNumInterpBits = 14;

// bits to shift the phase fraction down to avoid overflow
int kPreInterpShift = 30 - 14;

typedef struct {
    int32_t a, b, c, y0, y1, y2, y3;
} state;

void init();

static inline int32_t interp(state* p, int32_t x) {
    return (((((p->a * x >> 14) + p->b) * x >> 14) + p->c) * x >> 14) + p->y1;
}

static inline void advance(state* p, int16_t in) {
    p->y0 = p->y1;
    p->y1 = p->y2;
    p->y2 = p->y3;
    p->y3 = in;
    p->a = (3 * (p->y1 - p->y2) - p->y0 + p->y3) >> 1;
    p->b = (p->y2 << 1) + p->y0 - (((5 * p->y1 + p->y3)) >> 1);
    p->c = (p->y2 - p->y0) >> 1;
}

state left, right;

// multiplier to calculate fixed point phase increment
double kPhaseMultiplier = 1L << 30;
const int32_t mBitDepth = 16;
const int32_t mChannelCount = 2;
const int32_t mSampleRate = 44100;
int32_t mInSampleRate = 48000;
size_t mInputIndex = 0;
int32_t mPhaseIncrement = 0;
uint32_t mPhaseFraction = 0;

#endif /*ANDROID_AUDIO_RESAMPLER_CUBIC_H*/
