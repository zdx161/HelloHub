#include <stdio.h>
#include <stdio.h>
#include "common.h"

int alocate_buffer(uchar **pcm, int size)
{
    int ret = 0;
    printf("point addr %p\n", pcm);
    *pcm = (uchar *)malloc(size * sizeof(uchar));
    if(*pcm == NULL){
        printf("alocate buffer failed.\n");
        ret = -1;
    }

    return ret;
}

void free_buffer(uchar **pcm)
{
    if(*pcm != NULL){
        printf("free memory!\n");
        free(*pcm);
        *pcm = NULL;
    }

}
