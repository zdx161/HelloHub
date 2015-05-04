#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include "AudioResamplerCubic.h"

typedef struct {
    union {
        void * raw;
        short * i16;
        int8_t * i8;
    };
    size_t frameCount;
} Buffer_t;

uint32_t kPhaseMask = (1LU << 30) - 1;

void init() {
    memset(&left, 0, sizeof(state));
    memset(&right, 0, sizeof(state));
}

void setSampleRate(int32_t inSampleRate) {
    mInSampleRate = inSampleRate;
    mPhaseIncrement = (uint32_t)((kPhaseMultiplier * inSampleRate) / mSampleRate);
}

int resampleStereo16(int32_t* out, size_t outFrameCount, Buffer_t * mBuffer)
{
    size_t inputIndex = mInputIndex;
    uint32_t phaseFraction = mPhaseFraction;
    uint32_t phaseIncrement = mPhaseIncrement;
    size_t outputIndex = 0;
    size_t outputSampleCount = outFrameCount * 2;
    size_t inFrameCount = (outFrameCount*mInSampleRate)/mSampleRate;

    int16_t *in = mBuffer->i16;

    while (outputIndex < outputSampleCount) {
        int32_t sample;
        int32_t x;

        // calculate output sample
        x = phaseFraction >> kPreInterpShift;
        out[outputIndex++] += interp(&left, x);
        out[outputIndex++] += interp(&right, x);

        // increment phase
        phaseFraction += phaseIncrement;
        uint32_t indexIncrement = (phaseFraction >> 30);
        phaseFraction &= kPhaseMask;

        // time to fetch another sample
        while (indexIncrement--) {
            inputIndex++;
            if (inputIndex == mBuffer->frameCount) {
                inputIndex = 0;
                goto exit_fun;
            }
            // advance sample state
            advance(&left, in[inputIndex*2]);
            advance(&right, in[inputIndex*2+1]);
        }
    }
exit_fun:
    return outputIndex;
}

#define TEST_RESAMPLE
#ifdef TEST_RESAMPLE
static inline int16_t clamp16(int32_t sample)
{
    if ((sample>>15) ^ (sample>>31))
        sample = 0x7FFF ^ (sample>>31);
    return sample;
}


int main(int  argc, char ** argv)
{
    Buffer_t *mBuffer;
    int32_t outbuf[48000*2] = {0};
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
    fread(mBuffer->raw, 1, size, in);
    mBuffer->frameCount = 48000;

    init();
    setSampleRate(48000);
    int outsize = resampleStereo16(outbuf, 44100, mBuffer);

    size_t i;
    int * sums = outbuf;
    for (i = 0; i < outsize / 2; i++) {
        int32_t l = *sums++;
        int32_t r = *sums++;
        l = clamp16(l);
        r = clamp16(r);
        int tmp = (r<<16) | (l & 0xFFFF);
        fwrite(&tmp, sizeof(int), 1, out);
    }

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
