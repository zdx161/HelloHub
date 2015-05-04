#ifndef ANDROID_AUDIO_RESAMPLER_H
#define ANDROID_AUDIO_RESAMPLER_H

#include <stdint.h>
#include <sys/types.h>


typedef unsigned int uint32_t;
typedef int int32_t;

// number of bits for phase fraction - 30 bits allows nearly 2x downsampling
int kNumPhaseBits = 30;

// phase mask for fraction
uint32_t kPhaseMask = (1LU<<30)-1;

// multiplier to calculate fixed point phase increment
double kPhaseMultiplier = 1L << 30;
const int32_t mBitDepth = 16;
const int32_t mChannelCount = 2;
const int32_t mSampleRate = 44100;
int32_t mInSampleRate = 48000;
size_t mInputIndex = 0;
int32_t mPhaseIncrement = 0;
uint32_t mPhaseFraction = 0;

#endif // ANDROID_AUDIO_RESAMPLER_H
