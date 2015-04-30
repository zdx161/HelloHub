#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include "audioresample.h"



// number of bits used in interpolation multiply - 15 bits avoids overflow
static const int kNumInterpBits = 15;

// bits to shift the phase fraction down to avoid overflow
static const int kPreInterpShift = kNumPhaseBits - kNumInterpBits;

static inline int32_t Interp(int32_t x0, int32_t x1, uint32_t f) {
    return x0 + (((x1 - x0) * (int32_t)(f >> kPreInterpShift)) >> kNumInterpBits);
}

static inline void Advance(size_t* index, uint32_t* frac, uint32_t inc) {
    *frac += inc;
    *index += (size_t)(*frac >> kNumPhaseBits);
    *frac &= kPhaseMask;
}

int mX0L = 0;
int mX0R = 0;


int initSampleRate(int bitDepth, int inChannelCount, int32_t sampleRate, src_quality quality)
{
    mBitDepth(bitDepth), mChannelCount(inChannelCount),
            mSampleRate(sampleRate), mInSampleRate(sampleRate),mInputIndex(0),
            mPhaseFraction(0), mLocalTimeFreq(0),
            mPTS(AudioBufferProvider::kInvalidPTS), mQuality(quality)
    // sanity check on format
    if ((bitDepth != 16) ||(inChannelCount < 1) || (inChannelCount > 2)) {
        ALOGE("Unsupported sample format, %d bits, %d channels", bitDepth,
                inChannelCount);
    }
    if (sampleRate <= 0) {
        ALOGE("Unsupported sample rate %d Hz", sampleRate);
    }

    // initialize common members
    mVolume[0] = mVolume[1] = 0;
    mBuffer.frameCount = 0;

}

void setSampleRate(int32_t inSampleRate) {
    mInSampleRate = inSampleRate;
    mPhaseIncrement = (uint32_t)((kPhaseMultiplier * inSampleRate) / mSampleRate);
}

void setVolume(int16_t left, int16_t right) {
    mVolume[0] = left;
    mVolume[1] = right;
}

void setLocalTimeFreq(uint64_t freq) {
    mLocalTimeFreq = freq;
}

void setPTS(int64_t pts) {
    mPTS = pts;
}

int64_t calculateOutputPTS(int outputFrameIndex) {

    if (mPTS == AudioBufferProvider::kInvalidPTS) {
        return AudioBufferProvider::kInvalidPTS;
    } else {
        return mPTS + ((outputFrameIndex * mLocalTimeFreq) / mSampleRate);
    }
}

void reset() {
    mInputIndex = 0;
    mPhaseFraction = 0;
    mBuffer.frameCount = 0;
}

// ----------------------------------------------------------------------------

void resample(int32_t* out, size_t outFrameCount,
        AudioBufferProvider* provider) {
    // should never happen, but we overflow if it does
    // select the appropriate resampler
    switch (mChannelCount) {
    case 1:
        resampleMono16(out, outFrameCount, provider);
        break;
    case 2:
        resampleStereo16(out, outFrameCount, provider);
        break;
    }
}

void resampleStereo16(int32_t* out, size_t outFrameCount,
        AudioBufferProvider* provider) {

    int32_t vl = mVolume[0];
    int32_t vr = mVolume[1];

    size_t inputIndex = mInputIndex;
    uint32_t phaseFraction = mPhaseFraction;
    uint32_t phaseIncrement = mPhaseIncrement;
    size_t outputIndex = 0;
    size_t outputSampleCount = outFrameCount * 2;
    size_t inFrameCount = (outFrameCount*mInSampleRate)/mSampleRate;

    while (outputIndex < outputSampleCount) {

        // buffer is empty, fetch a new one
        while (mBuffer.frameCount == 0) {
            mBuffer.frameCount = inFrameCount;
            provider->getNextBuffer(&mBuffer,
                                    calculateOutputPTS(outputIndex / 2));
            if (mBuffer.raw == NULL) {
                goto resampleStereo16_exit;
            }

            if (mBuffer.frameCount > inputIndex) break;

            inputIndex -= mBuffer.frameCount;
            mX0L = mBuffer.i16[mBuffer.frameCount*2-2];
            mX0R = mBuffer.i16[mBuffer.frameCount*2-1];
            provider->releaseBuffer(&mBuffer);
            // mBuffer.frameCount == 0 now so we reload a new buffer
        }

        int16_t *in = mBuffer.i16;

        // handle boundary case
        while (inputIndex == 0) {
            out[outputIndex++] += vl * Interp(mX0L, in[0], phaseFraction);
            out[outputIndex++] += vr * Interp(mX0R, in[1], phaseFraction);
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
            if (outputIndex == outputSampleCount)
                break;
        }

        // process input samples
        while (outputIndex < outputSampleCount && inputIndex < mBuffer.frameCount) {
            out[outputIndex++] += vl * Interp(in[inputIndex*2-2],
                    in[inputIndex*2], phaseFraction);
            out[outputIndex++] += vr * Interp(in[inputIndex*2-1],
                    in[inputIndex*2+1], phaseFraction);
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
        }

        // if done with buffer, save samples
        if (inputIndex >= mBuffer.frameCount) {
            inputIndex -= mBuffer.frameCount;

            mX0L = mBuffer.i16[mBuffer.frameCount*2-2];
            mX0R = mBuffer.i16[mBuffer.frameCount*2-1];
            provider->releaseBuffer(&mBuffer);

            // verify that the releaseBuffer resets the buffer frameCount
        }
    }

resampleStereo16_exit:
    // save state
    mInputIndex = inputIndex;
    mPhaseFraction = phaseFraction;
}

void resampleMono16(int32_t* out, size_t outFrameCount,
        AudioBufferProvider* provider) {

    int32_t vl = mVolume[0];
    int32_t vr = mVolume[1];

    size_t inputIndex = mInputIndex;
    uint32_t phaseFraction = mPhaseFraction;
    uint32_t phaseIncrement = mPhaseIncrement;
    size_t outputIndex = 0;
    size_t outputSampleCount = outFrameCount * 2;
    size_t inFrameCount = (outFrameCount*mInSampleRate)/mSampleRate;

    //      outFrameCount, inputIndex, phaseFraction, phaseIncrement);
    while (outputIndex < outputSampleCount) {
        // buffer is empty, fetch a new one
        while (mBuffer.frameCount == 0) {
            mBuffer.frameCount = inFrameCount;
            provider->getNextBuffer(&mBuffer,
                                    calculateOutputPTS(outputIndex / 2));
            if (mBuffer.raw == NULL) {
                mInputIndex = inputIndex;
                mPhaseFraction = phaseFraction;
                goto resampleMono16_exit;
            }
            if (mBuffer.frameCount >  inputIndex) break;

            inputIndex -= mBuffer.frameCount;
            mX0L = mBuffer.i16[mBuffer.frameCount-1];
            provider->releaseBuffer(&mBuffer);
            // mBuffer.frameCount == 0 now so we reload a new buffer
        }
        int16_t *in = mBuffer.i16;

        // handle boundary case
        while (inputIndex == 0) {
            // ALOGE("boundary case");
            int32_t sample = Interp(mX0L, in[0], phaseFraction);
            out[outputIndex++] += vl * sample;
            out[outputIndex++] += vr * sample;
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
            if (outputIndex == outputSampleCount)
                break;
        }

        // process input samples
        while (outputIndex < outputSampleCount && inputIndex < mBuffer.frameCount) {
            int32_t sample = Interp(in[inputIndex-1], in[inputIndex],
                    phaseFraction);
            out[outputIndex++] += vl * sample;
            out[outputIndex++] += vr * sample;
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
        }

        // if done with buffer, save samples
        if (inputIndex >= mBuffer.frameCount) {
            inputIndex -= mBuffer.frameCount;

            mX0L = mBuffer.i16[mBuffer.frameCount-1];
            provider->releaseBuffer(&mBuffer);
        }
    }

resampleMono16_exit:
    // save state
    mInputIndex = inputIndex;
    mPhaseFraction = phaseFraction;
}



#define TEST_RESAMPLE
#ifdef TEST_RESAMPLE

int main(int  argc, char ** argv)
{

   AudioResampler *resampler;
   resampler = new AudioResamplerOrder1(bitDepth, inChannelCount, sampleRate);
   delete resampler;

    return 0;
}

#endif
