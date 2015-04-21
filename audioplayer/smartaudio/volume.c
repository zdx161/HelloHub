#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    int mIndex;
    float mDBAttenuation;
} VolumeCurvePoint;

typedef unsigned int uint32_t;

typedef struct {
    uint32_t volL;
    uint32_t volR;
} Volume;


enum { VOLMIN = 0, VOLKNEE1 = 1, VOLKNEE2 = 2, VOLMAX = 3, VOLCNT = 4};

const VolumeCurvePoint curve[VOLCNT] = {
    {1, -56.0f}, {20, -34.0f}, {60, -11.0f}, {100, 0.0f}
};

enum {mIndexMin = 0, mIndexMax = 15};

uint32_t volumeRL = 0x10001000; //8.24 format

Volume applyvolume(float amplification)
{
    uint32_t vl, vr;
    float v = amplification;
    Volume vol;

    vl = volumeRL & 0xFFFF;
    vr = volumeRL >> 16;
    // now apply the master volume and stream type volume
    vl = (uint32_t)(v * vl) << 12;
    vr = (uint32_t)(v * vr) << 12;

    // Convert volumes from 8.24 to 4.12 format
    // This additional clamping is needed in case chain->setVolume_l() overshot
    vl = (vl + (1 << 11)) >> 12;
    vr = (vr + (1 << 11)) >> 12;
    

    vol.volL = vl;
    vol.volR = vr;

    return vol;
}



float computeamplification(int indexInUi)
{

    int nbSteps = 1 + curve[VOLMAX].mIndex - curve[VOLMIN].mIndex;
    int volIdx = (nbSteps * (indexInUi - mIndexMin)) / (mIndexMax - mIndexMin);

    int segment = 0;
    if (volIdx < curve[VOLMIN].mIndex) {         // out of bounds
        return 0.0f;
    } else if (volIdx < curve[VOLKNEE1].mIndex) {
        segment = 0;
    } else if (volIdx < curve[VOLKNEE2].mIndex) {
        segment = 1;
    } else if (volIdx <= curve[VOLMAX].mIndex) {
        segment = 2;
    } else {                                                               // out of bounds
        return 1.0f;
    }


    // linear interpolation in the attenuation table in dB
    float decibels = curve[segment].mDBAttenuation +
            ((float)(volIdx - curve[segment].mIndex)) *
                ( (curve[segment+1].mDBAttenuation -
                        curve[segment].mDBAttenuation) /
                    ((float)(curve[segment+1].mIndex -
                            curve[segment].mIndex)) );

    float amplification = exp( decibels * 0.115129f); // exp( dB * ln(10) / 20 )

    return amplification;
}

#define FUN_TEST
#ifdef FUN_TEST
int main()
{

    int index;
    float amplification;
    uint32_t volL = 0;

    
    for (index = mIndexMin; index <= mIndexMax; index ++) {
        amplification = computeamplification(index);
        volL = applyvolume(amplification).volL;
        printf("index = %d, amplification = %f, R = %d\n", index, amplification, volL/*(unsigned int)(amplification * 4096)*/);
    }

    return 0;
}
#endif
