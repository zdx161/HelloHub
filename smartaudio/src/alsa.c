/*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* make ALSA 0.9.x compatible to the 1.0.x API */
#define ALSA_PCM_NEW_HW_PARAMS_API
#define ALSA_PCM_NEW_SW_PARAMS_API

#include <alsa/asoundlib.h>


/* My laptop has probs playing low-sampled files with only 0.5s buffer... this should be a user setting -- ThOr */
#define BUFFER_LENGTH 0.5	/* in seconds */

#if 0
static const struct {
	snd_pcm_format_t alsa;
	int format;
} format_map[] = {
	{ SND_PCM_FORMAT_S16,    MPG123_ENC_SIGNED_16   },
	{ SND_PCM_FORMAT_U16,    MPG123_ENC_UNSIGNED_16 },
	{ SND_PCM_FORMAT_U8,     MPG123_ENC_UNSIGNED_8  },
	{ SND_PCM_FORMAT_S8,     MPG123_ENC_SIGNED_8    },
	{ SND_PCM_FORMAT_A_LAW,  MPG123_ENC_ALAW_8      },
	{ SND_PCM_FORMAT_MU_LAW, MPG123_ENC_ULAW_8      },
	{ SND_PCM_FORMAT_S32,    MPG123_ENC_SIGNED_32   },
	{ SND_PCM_FORMAT_U32,    MPG123_ENC_UNSIGNED_32 },
	{ SND_PCM_FORMAT_S24_3LE, MPG123_ENC_SIGNED_24   },
	{ SND_PCM_FORMAT_U24_3LE, MPG123_ENC_UNSIGNED_24 },
	{ SND_PCM_FORMAT_FLOAT,  MPG123_ENC_FLOAT_32    },
	{ SND_PCM_FORMAT_FLOAT64, MPG123_ENC_FLOAT_64   }
};
#define NUM_FORMATS (sizeof format_map / sizeof format_map[0])
#endif

static int rates_match(long int desired, unsigned int actual)
{
	return actual * 100 > desired * (100 - AUDIO_RATE_TOLERANCE) &&
	       actual * 100 < desired * (100 + AUDIO_RATE_TOLERANCE);
}


typedef struct audio_output_struct
{
	int fn;			/* filenumber */
	void *userptr;	/* driver specific pointer */
	
	/* Callbacks */
	int (*open)(struct audio_output_struct *);
	int (*get_formats)(struct audio_output_struct *);
	int (*write)(struct audio_output_struct *, unsigned char *,int);
	void (*flush)(struct audio_output_struct *);
	int (*close)(struct audio_output_struct *);
	int (*deinit)(struct audio_output_struct *);
	
	/* the module this belongs to */
	//mpg123_module_t *module;
	
	char *device;	/* device name */
	int   flags;	/* some bits; namely headphone/speaker/line */
	long rate;		/* sample rate */
	long gain;		/* output gain */
	int channels;	/* number of channels */
	int format;		/* format flags */
	int is_open;	/* something opened? */
#define MPG123_OUT_QUIET 1
	int auxflags; /* For now just one: quiet mode (for probing). */
} audio_output_t;

static int initialize_device(audio_output_t *ao)
{
	snd_pcm_hw_params_t *hw=NULL;
	snd_pcm_sw_params_t *sw=NULL;
	snd_pcm_uframes_t buffer_size;
	snd_pcm_uframes_t period_size;
	snd_pcm_format_t format;
	snd_pcm_t *pcm=(snd_pcm_t*)ao->userptr;
	unsigned int rate;
	int i;

	snd_pcm_hw_params_alloca(&hw); /* Ignore GCC warning here... alsa-lib>=1.0.16 doesn't trigger that anymore, too. */
	if (snd_pcm_hw_params_any(pcm, hw) < 0) {
		if(!0) printf("initialize_device(): no configuration available");
		return -1;
	}
	if (snd_pcm_hw_params_set_access(pcm, hw, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
		if(!0) printf("initialize_device(): device does not support interleaved access");
		return -1;
	}

#if 0
	format = SND_PCM_FORMAT_UNKNOWN;
	for (i = 0; i < NUM_FORMATS; ++i) {
		if (ao->format == format_map[i].mpg123) {
			format = format_map[i].alsa;
			break;
		}
	}
	if (format == SND_PCM_FORMAT_UNKNOWN) {
		if(!0) printf("initialize_device(): invalid sample format %d", ao->format);
		errno = EINVAL;
		return -1;
	}
#endif
    format = SND_PCM_FORMAT_S16_LE;
	if (snd_pcm_hw_params_set_format(pcm, hw, format) < 0) {
		if(!0) printf("initialize_device(): cannot set format %s", snd_pcm_format_name(format));
		return -1;
	}
	if (snd_pcm_hw_params_set_channels(pcm, hw, ao->channels) < 0) {
		if(!0) printf("initialize_device(): cannot set %d channels", ao->channels);
		return -1;
	}
	rate = ao->rate;
	if (snd_pcm_hw_params_set_rate_near(pcm, hw, &rate, NULL) < 0) {
		if(!0) printf("initialize_device(): cannot set rate %u", rate);
		return -1;
	}
	if (!rates_match(ao->rate, rate)) {
		if(!0) error2("initialize_device(): rate %ld not available, using %u", ao->rate, rate);
		/* return -1; */
	}
	buffer_size = rate * BUFFER_LENGTH;
	if (snd_pcm_hw_params_set_buffer_size_near(pcm, hw, &buffer_size) < 0) {
		if(!0) printf("initialize_device(): cannot set buffer size");
		return -1;
	}
	printf("buffer_size=%lu", (unsigned long)buffer_size);
	period_size = buffer_size / 4;
	if (snd_pcm_hw_params_set_period_size_near(pcm, hw, &period_size, NULL) < 0) {
		if(!0) printf("initialize_device(): cannot set period size");
		return -1;
	}
	if (snd_pcm_hw_params(pcm, hw) < 0) {
		if(!0) printf("initialize_device(): cannot set hw params");
		return -1;
	}

	snd_pcm_sw_params_alloca(&sw);
	if (snd_pcm_sw_params_current(pcm, sw) < 0) {
		if(!0) printf("initialize_device(): cannot get sw params");
		return -1;
	}
	/* start playing right away */
	if (snd_pcm_sw_params_set_start_threshold(pcm, sw, 1) < 0) {
		if(!0) printf("initialize_device(): cannot set start threshold");
		return -1;
	}
	/* wake up on every interrupt */
	if (snd_pcm_sw_params_set_avail_min(pcm, sw, 1) < 0) {
		if(!0) printf("initialize_device(): cannot set min available");
		return -1;
	}
#if SND_LIB_VERSION < ((1<<16)|16)
	/* Always write as many frames as possible (deprecated since alsa-lib 1.0.16) */
	if (snd_pcm_sw_params_set_xfer_align(pcm, sw, 1) < 0) {
		if(!0) printf("initialize_device(): cannot set transfer alignment");
		return -1;
	}
#endif
	if (snd_pcm_sw_params(pcm, sw) < 0) {
		if(!0) printf("initialize_device(): cannot set sw params");
		return -1;
	}
	return 0;
}

static void error_ignorer(const char *file, int line, const char *function, int err, const char *fmt,...)
{
	/* I can make ALSA silent. */
}

static int open_alsa(audio_output_t *ao)
{
	const char *pcm_name;
	snd_pcm_t *pcm=NULL;
	printf("open_alsa with %p", ao->userptr);

#ifndef DEBUG
	if(0) snd_lib_error_set_handler(error_ignorer);
#endif

	pcm_name = ao->device ? ao->device : "default";
	if (snd_pcm_open(&pcm, pcm_name, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
		if(!0) printf("cannot open device %s", pcm_name);
		return -1;
	}
	ao->userptr = pcm;
	if (ao->format != -1) {
		/* we're going to play: initalize sample format */
		return initialize_device(ao);
	} else {
		/* query mode; sample format will be set for each query */
		return 0;
	}
}


static int get_formats_alsa(audio_output_t *ao)
{
	snd_pcm_t *pcm=(snd_pcm_t*)ao->userptr;
	snd_pcm_hw_params_t *hw;
	unsigned int rate;
	int supported_formats, i;

	snd_pcm_hw_params_alloca(&hw);
	if (snd_pcm_hw_params_any(pcm, hw) < 0) {
		if(!0) printf("get_formats_alsa(): no configuration available");
		return -1;
	}
	if (snd_pcm_hw_params_set_access(pcm, hw, SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
		return -1;
	if (snd_pcm_hw_params_set_channels(pcm, hw, ao->channels) < 0)
		return 0;
	rate = ao->rate;
	if (snd_pcm_hw_params_set_rate_near(pcm, hw, &rate, NULL) < 0)
		return -1;
	if (!rates_match(ao->rate, rate))
		return 0;
	supported_formats = 0;
	for (i = 0; i < NUM_FORMATS; ++i) {
		if (snd_pcm_hw_params_test_format(pcm, hw, format_map[i].alsa) == 0)
			supported_formats |= format_map[i].mpg123;
	}
	return supported_formats;
}

static int write_alsa(audio_output_t *ao, unsigned char *buf, int bytes)
{
	snd_pcm_t *pcm=(snd_pcm_t*)ao->userptr;
	snd_pcm_uframes_t frames;
	snd_pcm_sframes_t written;

	frames = snd_pcm_bytes_to_frames(pcm, bytes);
	while
	( /* Try to write, recover if error, try again if recovery successful. */
		(written = snd_pcm_writei(pcm, buf, frames)) < 0
		&& snd_pcm_recover(pcm, (int)written, 0) == 0
	)
	{
		printf("recovered from alsa issue %i while trying to write %lu frames", (int)written, (unsigned long)frames);
	}
	if(written < 0)
	{
		printf("Fatal problem with alsa output, error %i.", written);
		return -1;
	}
	else return snd_pcm_frames_to_bytes(pcm, written);
}

static void flush_alsa(audio_output_t *ao)
{
	snd_pcm_t *pcm=(snd_pcm_t*)ao->userptr;

	/* is this the optimal solution? - we should figure out what we really whant from this function */

printf("alsa drop");
	snd_pcm_drop(pcm);
printf("alsa prepare");
	snd_pcm_prepare(pcm);
printf("alsa flush done");
}

static int close_alsa(audio_output_t *ao)
{
	snd_pcm_t *pcm=(snd_pcm_t*)ao->userptr;
	printf("close_alsa with %p", ao->userptr);
	if(pcm != NULL) /* be really generous for being called without any device opening */
	{
		snd_pcm_drain(pcm); /* If there is something, let it drain, always. */
		ao->userptr = NULL; /* Should alsa do this or the module wrapper? */
		return snd_pcm_close(pcm);
	}
	else return 0;
}

typedef struct audio_output_pthread{
    int pexit;
    int pcmnum;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    audio_output_t *ao;
    char pcmbuf[44100 * 2 * 2];
} audio_output_pthread_t;


void * input(void *in)
{
    if(in == NULL)
    {
        goto exit;
    }
    audio_output_pthread_t * aopt = (audio_output_pthread_t *) in;

    if(0 == aopt->ao->open(aopt->ao)){
        printf("open alsa failed.\n");
        goto exit;
    }
            
    while(!aopt->pexit){
        pthread_mutex_lock(&aopt->mutex);
        while(aopt->pcmnum <= 0 && aopt->pexit == 0){
            pthread_cond_wait(&aopt->cond, &aopt->mutex);
        }

        if(aopt->pcmnum > 0 && aopt->pexit == 0){
            int writen = 0;
            writen = aopt->ao->write(aopt->ao, aopt->pcm_buf, aopt->pcmnum);
            if(writen < aopt->pcmnum){
                memcpy(aopt->pcmbuf, (char *)(aopt->pcmbuf + writen), aopt->pcmnum-writen);
                aopt->pcmnum -= writen;
            }
        }
        pthread_mutex_unlock(aopt->mutex);

    }

exit:
    printf("======pthread exit=====\n")
    pthread_exit(NULL);
    return (void *)0;
}


void * output(void * out)
{

exit:
    printf("=====output thread exit=====\n");
    pthread_exit(NULL);
    return (void *)0;
}

int main(void)
{
    pthread_t pidout, pidinput;
    
    audio_output_pthread_t * aopt;
    aopt = (audio_output_pthread_t *) malloc(sizeof(audio_output_pthread_t));
    if(aopt == NULL){
        printf("aopt malloc failed.\n");
        return 0;
    }
    
    memset(aopt, 0, sizeof(audio_output_pthread_t));


    aopt->ao = (audio_output_t *) malloc (sizeof(audio_output_t));
    if(aopt->ao == NULL){
        printf("allocate ao memory failed.\n");
        return -1;
    }
    memset(aopt, 0, sizeof(audio_output_t));

    aopt->ao->open = open_alsa;
    aopt->ao->flush = flush_alsa;
    aopt->ao->write = write_alsa;
    aopt->ao->get_formats = get_formats_alsa;
    aopt->ao->close = close_alsa;

    aopt->ao->device = strdup("plughw:0,0");  
    aopt->ao->rate = 44100;
    aopt->ao->channels = 2;
    aopt->ao->format = SND_PCM_FORMAT_S16_LE;
    aopt->cond = PTHREAD_COND_INITIALIZER;
    aopt->mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_create(&pidinput, NULL, input, aopt);
    pthread_create(&pidout, NULL, output, aopt);
    
    pthread_join(pidinput, NULL);
    pthread_join(pidout, NULL);

    if(0 == ao->open(ao)){
        printf("open alsa failed.\n");
        return -1;
    }

    

    

    ao->close(ao);

    return 0;
}

#if 0
static int init_alsa(audio_output_t* ao)
{
	if (ao==NULL) return -1;

	/* Set callbacks */
	ao->open = open_alsa;
	ao->flush = flush_alsa;
	ao->write = write_alsa;
	ao->get_formats = get_formats_alsa;
	ao->close = close_alsa;

	/* Success */
	return 0;
}



/* 
	Module information data structure
*/
mpg123_module_t mpg123_output_module_info = {
	/* api_version */	MPG123_MODULE_API_VERSION,
	/* name */			"alsa",						
	/* description */	"Output audio using Advanced Linux Sound Architecture (ALSA).",
	/* revision */		"$Rev:$",						
	/* handle */		NULL,
	
	/* init_output */	init_alsa,						
};
#endif
