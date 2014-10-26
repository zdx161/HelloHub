#include <stdio.h>
#include <getopt.h>
#include "option.h"


struct option long_option[] =
{
    {"help", 0, NULL, 'h'},
    {"rate", 1, NULL, 'r'},
    {"channels", 1, NULL, 'c'},
    {"frequency", 1, NULL, 'f'},
    {"duration", 1, NULL, 'd'},
    {"format", 1, NULL, 'o'},
    {"amplitude", 1, NULL, 'a'},
    {NULL, 0, NULL, 0},
};

void show_info(void)
{
    printf("  %s version 0.1 release, Copyright (c) %d-%d the SoftWare developers\n", 
            NAME, 2014, 2014);
    printf("  built on %s %s with %s %s\n", __DATE__, __TIME__, CC_TYPE, CC_VERSION);
}
void help(void)
{
    printf(
        "\n  Usage: icanwav [OPTION] ...\n"
        "    -h,--help	help\n"
        "    -r,--rate	stream rate in Hz\n"
        "    -c,--channels	count of channels in stream\n"
        "    -f,--frequency	sine wave frequency in Hz\n"
        "    -d,--duration	audio duration in seconds\n"
        "    -o,--format	sample format\n"
        "    -a,--amplitude amplitude is in db\n"
        "\n");
}

void print_config(AudioInfo optinfo)
{
    //printf("***********************************************************\n");
    printf("  Show you configuration information: \n");
    printf("  channels:      %d ch\n", optinfo.channels);
    printf("  samplerate:    %d HZ\n", optinfo.rate);
    printf("  bitspersample: %d bps\n", optinfo.bps);
    printf("  amplitude:     %d db\n", optinfo.decibel*6);
    printf("  duration:      %d s\n", optinfo.duration);
    //printf("***********************************************************\n");
    //printf("   \n");
}

void set_default_config(AudioInfo *definfo)
{
    definfo->channels = 2;
    definfo->rate = 44100;
    definfo->bps = 16;
    definfo->decibel = 0;
    definfo->duration = 10;
}

int parse_option(int argc, char **argv, AudioInfo *optinfo)
{
    int morehelp = 0;
    int rate;
    int channels;
    int freq;
    int period_time;
    int decibel;

    while (1) {
        int c;
        if ((c = getopt_long(argc, argv, "hr:c:f:d:o:a:xyz", long_option, NULL)) < 0){
            if(argc == 1)
                morehelp = 2;
            break;
        }

        switch (c) {
            case 'h':
                morehelp = 1;
                break;
            case 'r':
                rate = atoi(optarg);
                rate = rate < 4000 ? 4000 : rate;
                rate = rate > 196000 ? 196000 : rate;
                optinfo->rate = rate;
                break;
            case 'c':
                channels = atoi(optarg);
                channels = channels < 1 ? 1 : channels;
                channels = channels > 1024 ? 1024 : channels;
                optinfo->channels = channels;
                break;
            case 'f':
                freq = atoi(optarg);
                freq = freq < 50 ? 50 : freq;
                freq = freq > 5000 ? 5000 : freq;
                break;
            case 'd':
                period_time = atoi(optarg);
                period_time = period_time < 10 ? 10 : period_time;
                period_time = period_time > 60 ? 60 : period_time;
                optinfo->duration = period_time; 
                break;
            case 'o':
                printf("served set config item\n");
                break;
            case 'a':
                decibel = atoi(optarg);
                decibel = decibel < 0 ? -decibel : decibel;
                decibel = decibel / 6;
                optinfo->decibel = decibel;
                break;
            case 'x':
                morehelp = 1;
                break;
            case 'y':
                morehelp = 1;
                break;
            case 'z':
                morehelp = 1;
                break;
            default:
                printf("can not support option: %c\n", c);
                morehelp = 1;
                break;
        }
    }

    return morehelp;
}
