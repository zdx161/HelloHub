#ifndef COMPUTE_VOLUME_H
#define COMPUTE_VOLUME_H

typedef unsigned int uint32_t;
typedef int int32_t;
typedef short int16_t;

typedef struct {
    uint32_t volL;
    uint32_t volR;
} Volume;


int32_t mulRL(int left, uint32_t inRL, uint32_t vRL);
Volume applyvolume(float amplification);
float computeamplification(int indexInUi);

#endif
