#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int alocate_buffer(void **pcm, int size)
{
    int ret = 0;
    printf("point addr %p\n", pcm);
    *pcm = (void *)malloc(size * sizeof(uchar));
    if(*pcm == NULL){
        printf("alocate buffer failed.\n");
        ret = -1;
    }

    return ret;
}

void free_buffer(void **pcm)
{
    if(*pcm != NULL){
        printf("free memory!\n");
        free(*pcm);
        *pcm = NULL;
    }

}
