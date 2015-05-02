#ifndef ANDROID_AUDIO_RESAMPLER_H
#define ANDROID_AUDIO_RESAMPLER_H

#include <stdint.h>
#include <sys/types.h>




// number of bits for phase fraction - 30 bits allows nearly 2x downsampling
static const int kNumPhaseBits = 30;

// phase mask for fraction
static const uint32_t kPhaseMask = (1LU<<kNumPhaseBits)-1;

// multiplier to calculate fixed point phase increment
static const double kPhaseMultiplier = 1L << kNumPhaseBits;
const int32_t mBitDepth = 16;
const int32_t mChannelCount = 2;
const int32_t mSampleRate = 44100;
int32_t mInSampleRate = 48000;
size_t mInputIndex = 0;
int32_t mPhaseIncrement = 0;
uint32_t mPhaseFraction = 0;

#endif // ANDROID_AUDIO_RESAMPLER_H
