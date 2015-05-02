#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include "audioresample.h"

typedef  struct{
   union {
       void*       raw;
       short*      i16;
       int8_t*     i8; 
   };  
   size_t frameCount;
} Buffer_t;  

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

void setSampleRate(int32_t inSampleRate) {
    mInSampleRate = inSampleRate;
    mPhaseIncrement = (uint32_t)((kPhaseMultiplier * inSampleRate) / mSampleRate);
}

// ----------------------------------------------------------------------------
void resampleStereo16(int32_t* out, size_t outFrameCount, Buffer_t mBuffer )
{
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
            //TODO:get mBuffer
            if (mBuffer.raw == NULL) {
                goto resampleStereo16_exit;
            }

            if (mBuffer.frameCount > inputIndex) break;

            inputIndex -= mBuffer.frameCount;
            mX0L = mBuffer.i16[mBuffer.frameCount*2-2];
            mX0R = mBuffer.i16[mBuffer.frameCount*2-1];
            //TODO:release buffer
        }

        int16_t *in = mBuffer.i16;

        // handle boundary case
        while (inputIndex == 0) {
            out[outputIndex++] += Interp(mX0L, in[0], phaseFraction);
            out[outputIndex++] += Interp(mX0R, in[1], phaseFraction);
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
            if (outputIndex == outputSampleCount)
                break;
        }

        // process input samples
        while (outputIndex < outputSampleCount && inputIndex < mBuffer.frameCount) {
            out[outputIndex++] += Interp(in[inputIndex*2-2],
                    in[inputIndex*2], phaseFraction);
            out[outputIndex++] += Interp(in[inputIndex*2-1],
                    in[inputIndex*2+1], phaseFraction);
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
        }

        // if done with buffer, save samples
        if (inputIndex >= mBuffer.frameCount) {
            inputIndex -= mBuffer.frameCount;

            mX0L = mBuffer.i16[mBuffer.frameCount*2-2];
            mX0R = mBuffer.i16[mBuffer.frameCount*2-1];
            //TODO:release buffer
        }
    }

resampleStereo16_exit:
    // save state
    mInputIndex = inputIndex;
    mPhaseFraction = phaseFraction;
}


#define TEST_RESAMPLE
#ifdef TEST_RESAMPLE

int main(int  argc, char ** argv)
{
    Buffer_t *mBuffer;
    int size = 0;
    FILE *in = NULL;
    FILE *out= NULL;
    
    in = fopen(argv[1], "rb");
    out = fopen(argv[2], "wb");

    if (in == NULL || out == NULL)
        goto err;

    fseek(in, 0L, SEEK_END);
    size = ftell(in);
    printf("file size: %d\n", size);
    fseek(in, 0L, SEEK_SET);

    mBuffer = (Buffer_t *) calloc(1, sizeof(Buffer_t) + size);
    if (mBuffer == NULL) {
        printf("allocate memory failed.\n");
        goto err;
    }

    mBuffer->raw = mBuffer + sizeof(Buffer_t);



err:
    if (in != NULL)
        free(in);
    if (out != NULL)
        free(out);

    if (mBuffer != NULL)
        free(mBuffer);

    return 0;
}

#endif
