#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "option.h"
#include "pcm.h"
#include "wav.h"


int main(int argc, char **argv)
{
    int ret = 0;
    int freq = 440;
    int period_time = 10; //audio duration (seconds)
    int period;
    int size;
    int morehelp = 0;
    uchar *pcm;
    double _phase = 8.4199314187571872e-13;
    AudioInfo info;
   
    set_default_config(&info);

    morehelp = parse_option(argc, argv, &info);
    if (morehelp == 1) {
        help();
        return 0;
    }else if(morehelp == 2){
        printf("\n===using default set configuration===\n");
    }

    print_config(info);

    period = period_time * info.rate;

    printf("pcm: %p\n", &pcm);
    size = period * info.channels * info.bps / 8;
    printf("audio buffer size is: %d\n", size);
    ret = alocate_buffer(&pcm, size);

    if(ret != 0){
        printf("alocate audio buffer failed\n");
        return -1;
    }
    
    memset(pcm, 0, size);
    generate_sine(0, period, &_phase, freq, info, pcm);
    write_wav(info, pcm, size); //need implment

    if(ret == 0){
        free_buffer(&pcm);
        printf("pcm: %p\n", pcm);
    }

    return 0;
}
