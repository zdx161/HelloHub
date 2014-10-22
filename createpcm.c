#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>

static void generate_sine(/*const snd_pcm_channel_area_t *areas,*/ 
			  /*snd_pcm_uframes_t*/int offset,
			  int count, double *_phase, int channels, int freq, int format_bits, int rate)
{
	static double max_phase = 2. * M_PI;
	double phase = *_phase;
	double step = max_phase*freq/(double)rate;
	//unsigned char *samples[channels];
	int steps[channels];
	unsigned int chn;
	//int format_bits = snd_pcm_format_width(format);
        printf("format_bits:%d\n", format_bits);
	unsigned int maxval = (1 << (format_bits - 1 - 1)) - 1;
        printf("maxval:%u\n", maxval);
	int bps = format_bits / 8;  /* bytes per sample */
	int phys_bps = /*snd_pcm_format_physical_width(format)*/ 16 / 8;
	int big_endian = 0;//snd_pcm_format_big_endian(format) == 1;
	int to_unsigned = 0;//snd_pcm_format_unsigned(format) == 1;
	int is_float = 0;/*(format == SND_PCM_FORMAT_FLOAT_LE ||
			format == SND_PCM_FORMAT_FLOAT_BE);*/
        FILE *fp=NULL;
        fp = fopen("dumppcm", "a+");
        if(fp == NULL)
            printf("open dump file failed.\n");

	/* verify and prepare the contents of areas */
	for (chn = 0; chn < channels; chn++) {
                /*
		if ((areas[chn].first % 8) != 0) {
			printf("areas[%i].first == %i, aborting...\n", chn, areas[chn].first);
			exit(EXIT_FAILURE);
		}*/

		//samples[chn] = /*(signed short *)*/(((unsigned char *)areas[chn].addr) + (areas[chn].first / 8));

                /*
		if ((areas[chn].step % 16) != 0) {
			printf("areas[%i].step == %i, aborting...\n", chn, areas[chn].step);
			exit(EXIT_FAILURE);
		}*/
                
		steps[chn] = /*areas[chn].step*/ 16 / 8;
		//samples[chn] += offset * steps[chn];
	}
	/* fill the channel areas */
	while (count-- > 0) {
		union {
			float f;
			int i;
		} fval;
		int res, i;
		if (is_float) {
			fval.f = sin(phase) * maxval;
			res = fval.i;
		} else
			res = sin(phase) * maxval;
		if (to_unsigned)
			res ^= 1U << (format_bits - 1);
		for (chn = 0; chn < channels; chn++) {
			/* Generate data in native endian format */
			if (big_endian) {
				for (i = 0; i < bps; i++)
					;//*(samples[chn] + phys_bps - 1 - i) = (res >> i * 8) & 0xff;
			} else {
				for (i = 0; i < bps; i++){
					//*(samples[chn] + i) = (res >>  i * 8) & 0xff;
                                        unsigned char sample =  (res >>  i * 8) & 0xff;
                                        if(i == 0)
                                            sample = 0;
                                            //*(samples[chn] + i) = 0;
                                        if(fp != NULL){
                                            fwrite((char*)(&sample/*samples[chn] + i*/), 1, 1,fp);     
                                        } 
                                }
			}
			//samples[chn] += steps[chn];
		}
		phase += step;
		if (phase >= max_phase)
			phase -= max_phase;
	}

	*_phase = phase;

        if(fp != NULL)
        {
             fclose(fp);
             fp = NULL;
        }
}


static void help(void)
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

static void print_config(int channels, int rate, int bps, int decibel)
{
    printf("====== show configuration info ======\n");
    printf(" channels: %d ch\n", channels); 
    printf(" rate: %d HZ\n", rate);
    printf(" bps: %d bit/sample\n", bps);
    printf(" decibel: %d db", decibel);
    printf("================end====================\n");
}
//static void generate_sine(/*const snd_pcm_channel_area_t *areas,*/ 
//			  snd_pcm_uframes_t offset,
//			  int count, double *_phase, int channels, int freq, int format_bits, int rate)
//#define CREATE_NAME() 

int main(int argc, char **argv)
{
    int channels = 2;
    int rate = 44100;
    int bps = 16;
    int decibel = 0;
    int freq = 440;
    int period_time = 1000;

    double _phase = 8.4199314187571872e-13; 

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

	int morehelp = 0;
	while (1) {
		int c;
		if ((c = getopt_long(argc, argv, "h:r:c:f:p:o", long_option, NULL)) < 0)
			break;
		switch (c) {
		case 'h':
			morehelp++;
			break;
		case 'r':
			rate = atoi(optarg);
			rate = rate < 4000 ? 4000 : rate;
			rate = rate > 196000 ? 196000 : rate;
			break;
		case 'c':
			channels = atoi(optarg);
			channels = channels < 1 ? 1 : channels;
			channels = channels > 1024 ? 1024 : channels;
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
        defaddult:
            printf("using default configuration:\n");
            break;
		}
	}

	if (morehelp) {
		help();
		return 0;
	}
    
    print_config(channels, channels, rate, decibel);

    //double _phase = 8.4199314187571872e-13; 
    //generate_sine(0, 441000, &_phase, 1, 440, 16, 44100);
  
    return 0;
}
