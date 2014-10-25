#include <stdio.h>
#include <getopt.h>
#include "option.h"

struct option long_option[] =
{
    {"help", 0, NULL, 'h'},
    {"rate", 1, NULL, 'r'},
    {"channels", 1, NULL, 'c'},
    {"frequency", 1, NULL, 'f'},
    {"period", 1, NULL, 'p'},
    {"format", 1, NULL, 'o'},
    {NULL, 0, NULL, 0},
};

void help(void)
{
    int k;
    printf(
        "Usage: createwav [OPTION]...\n"
        "-h,--help	help\n"
        "-r,--rate	stream rate in Hz\n"
        "-c,--channels	count of channels in stream\n"
        "-f,--frequency	sine wave frequency in Hz\n"
        "-p,--period	period size in us\n"
        "-o,--format	sample format\n"
        "\n");
#if 0
    printf("Recognized sample formats are:");

    for (k = 0; k < SND_PCM_FORMAT_LAST; ++k) {
        const char *s = snd_pcm_format_name(k);

        if (s)
            printf(" %s", s);
    }

    printf("\n");
    printf("Recognized transfer methods are:");

    for (k = 0; transfer_methods[k].name; k++)
        printf(" %s", transfer_methods[k].name);

    printf("\n");
#endif
}

void print_config(AudioInfo optinfo)
{
    printf("\n====== show configuration info ======\n");
    printf(" channels: %d ch\n", optinfo.channels);
    printf(" rate: %d HZ\n", optinfo.rate);
    printf(" bps: %d bit/sample\n", optinfo.bps);
    printf(" decibel: %d db\n", optinfo.decibel);
    printf("================end====================\n");
}

void set_default_config(AudioInfo *definfo)
{
    definfo->channels = 2;
    definfo->rate = 44100;
    definfo->bps = 16;
    definfo->decibel = 0;

}

int parse_option(int argc, char **argv, AudioInfo *optinfo)
{
    int morehelp = 0;
    int rate;
    int channels;
    int freq;
    int period_time;

    while (1) {
        int c;
        if ((c = getopt_long(argc, argv, "hr:c:f:p:o", long_option, NULL)) < 0){
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
            case 'p':
                period_time = atoi(optarg);
                period_time = period_time < 1000 ? 1000 : period_time;
                period_time = period_time > 1000000 ? 1000000 : period_time;
                break;
            case 'o':
                printf("served set config item\n");
                break;
            default:
                printf("can not support option: %c\n", c);
                morehelp = 1;
                break;
        }
    }

    return morehelp;
}
