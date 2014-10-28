#include <stdio.h>
#include <stdlib.h>
#include "wav.h"


void write_wav_header(void *header, AudioInfo info, int period)
{
    ChuckDes *descriptor;
    descriptor = (ChuckDes *) header;
    descriptor->ChunkID = 'R' | 'I'  << 8  | 'F' << 16 | 'F' << 24;
    //printf("ID:0x%x\n", descriptor->ChunkID);
    descriptor->ChunkSize = period + 36; //chunksize = filesize-8 (sizeof(RIFF) + sizeof(chunksize)) 
    descriptor->Format = 'W' | 'A' << 8 | 'V' << 16 | 'E' << 24;
    //printf("WAV:0x%x\n", descriptor->Format);

    SubchunkFMT *fmt;
    fmt = (SubchunkFMT *)(header+sizeof(ChuckDes));
    fmt->Subchunk1ID = 'f' | 'm' << 8 | 't' << 16 | ' ' << 24; 
    //printf("fmt:0x%x\n", fmt->Subchunk1ID);
    fmt->Subchunk1Size = 16;
    fmt->AudioForamt = 1; //pcm: default
    fmt->NumChannles = info.channels;
    fmt->SampleRate = info.rate;
    fmt->ByteRate = info.rate * info.channels * info.bps / 8;
    fmt->BlockAlign = info.channels * info.bps / 8;
    fmt->BitsPerSample = info.bps;

    SubchunkData * data = (SubchunkData*)(header+sizeof(ChuckDes)+sizeof(SubchunkFMT));
    data->Subchunk2ID = 'd' | 'a' << 8 | 't' << 16 | 'a' << 24;
    data->Subchunk2Size = period; //only pcm size, 36bytes contain sizeof(data) and sizeof(subchunk2size)
}

void write_wav(AudioInfo info, uchar *pcm, int size)
{
    void *head = NULL;
    char name[128] = {0};
    int hsize = 0;
    int ret = 0;
    FILE *fp = NULL;

    sprintf(name, "%dch_%dHZ_%dbits_%ddb_%dHZ_sine.wav", info.channels, info.rate, info.bps, info.decibel*6, info.frequency);
    //printf("name is %s\n", name);

    fp = fopen(name, "wb");
    if(fp == NULL){
        perror("open wav file failed.\n");
        exit(EXIT_FAILURE);
    }


    hsize = sizeof(ChuckDes) + sizeof(SubchunkFMT) + sizeof(SubchunkData); 
    
    ret = alocate_buffer(&head, hsize);
    if(ret != 0){
        printf("alocate wav header buffer failed.\n");
        goto out;
    }
    
    write_wav_header(head, info, size);
    fwrite((char*)head, sizeof(char), hsize, fp);
    fwrite((char*)pcm, sizeof(char), size, fp);

    if(ret == 0){
        free_buffer(&head);
        head = NULL;
    }

out:
    fclose(fp);
    //printf("\n***********************************************************\n");
    printf("\n  Congratulations! success to create wav file you need.  \n");
    printf("  saved to %s                      \n", name);
    //printf("***********************************************************\n");

}

#ifdef TEST

//the main work is to write wav header
//thd wav data is from generational sine wav function
int main(int argc, char **argv)
{
    
    FILE *fpr = NULL;
    FILE *fpw = NULL;
    fpr = fopen("dumppcm", "r"); 
    
    if(fpr == NULL){
        perror("open read file failed.\n");
        exit(EXIT_FAILURE);
    }
   
    fpw = fopen("dump.wav", "wb");
    if(fpw == NULL){
        perror("open write file failed.\n");
        exit(EXIT_FAILURE);
    }

    int fsize = 0;
    fsize = fseek(fpr, 0, SEEK_END);
    printf("fsize = %d\n", fsize);
    rewind(fpr);
    
 
    void *head = NULL;
    int hzise = sizeof(ChuckDes) + sizeof(SubchunkFMT) + sizeof(SubchunkData); 
    head = malloc(hzise); 
    if(head == NULL){
        printf("allocate head buffer failed\n");
    }else{ 
        //write_wav_header(head); 
        write_wav_header(head, 2, 44100, 16, 882000);
        fwrite((char*)head, 1, hzise, fpw);
        free(head);
        head = NULL;
        int c;
        while((c = fgetc(fpr)) != EOF){
            fputc(c, fpw);
        }
    }
    
   
    fclose(fpr);
    fclose(fpw);
    return 0;
}
#endif
