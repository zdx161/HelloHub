#ifndef ANDROID_AUDIO_RESAMPLER_SINC_H
#define ANDROID_AUDIO_RESAMPLER_SINC_H

#include <stdint.h>
#include <sys/types.h>

typedef short int16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

int16_t *mState;
int16_t *mImpulse;
int16_t *mRingFull;

const int32_t * mFirCoefs;
int32_t mFirCoefsDown[];
int32_t mFirCoefsUp[];

// ----------------------------------------------------------------------------
int32_t RESAMPLE_FIR_NUM_COEF       = 8;
int32_t RESAMPLE_FIR_LERP_INT_BITS  = 4;

// we have 16 coefs samples per zero-crossing
const int coefsBits = 4;        // 4
const int kNumPhaseBits = 30; 
const int cShift = 26;//kNumPhaseBits - coefsBits;            // 26
const uint32_t cMask  = ((1<<4)-1) << 26;    // 0xf<<26 = 3c00 0000

// and we use 15 bits to interpolate between these samples
// this cannot change because the mul below rely on it.
int pLerpBits = 15;
int pShift = 11;//kNumPhaseBits - coefsBits - pLerpBits;    // 11
uint32_t pMask  = ((1<<15)-1) << 11;    // 0x7fff << 11

int mInSampleRate = 0;
int mSampleRate = 44100;

// number of zero-crossing on each side
unsigned int halfNumCoefs = 8;//RESAMPLE_FIR_NUM_COEF;

#endif /*ANDROID_AUDIO_RESAMPLER_SINC_H*/
