#include <stdio.h>
#include <stdlib.h>

typedef unsigned int DWORD;
typedef unsigned short WORD;

typedef struct {
    DWORD ChunkID;
    DWORD ChunkSize;
    DWORD Format;
} ChuckDes;

typedef struct {
    DWORD Subchunk1ID;
    DWORD Subchunk1Size;
    WORD AudioForamt;
    WORD NumChannles;
    DWORD SampleRate;
    DWORD ByteRate;
    WORD BlockAlign;
    WORD BitsPerSample;
} SubchunkFMT;
typedef struct {
    DWORD Subchunk2ID;
    DWORD Subchunk2Size;
} SubchunkData;
void write_wav_header(void *header)
{
    ChuckDes *descriptor;
    descriptor = (ChuckDes *) header;
    descriptor->ChunkID = 'R' | 'I'  << 8  | 'F' << 16 | 'F' << 24;
    printf("ID:0x%x\n", descriptor->ChunkID);
    descriptor->ChunkSize = 882000 + 4 + 4 + 36; 
    descriptor->Format = 'W' | 'A' << 8 | 'V' << 16 | 'E' << 24;
    printf("WAV:0x%x\n", descriptor->Format);
    SubchunkFMT *fmt;
    fmt = (SubchunkFMT *)(header+sizeof(ChuckDes));
    fmt->Subchunk1ID = 'f' | 'm' << 8 | 't' << 16 | ' ' << 24; 
    printf("fmt:0x%x\n", fmt->Subchunk1ID);
    fmt->Subchunk1Size = 16;
    fmt->AudioForamt = 1;
    fmt->NumChannles = 1;
    fmt->SampleRate = 44100;
    fmt->ByteRate = 44100 * 1 * 16 / 8;
    fmt->BlockAlign = 2;//4;
    fmt->BitsPerSample = 16;
    SubchunkData * data = (SubchunkData*)(header+sizeof(ChuckDes)+sizeof(SubchunkFMT));
    data->Subchunk2ID = 'd' | 'a' << 8 | 't' << 16 | 'a' << 24;
    data->Subchunk2Size = 882000 + 4 + 4;
}


int main()
{
    
    FILE *fpr = NULL;
    FILE *fpw = NULL;
    fpr = fopen("dumppcm", "r"); 
    
    if(fpr == NULL){
        perror("open read file failed.\n");
        exit(EXIT_FAILURE);
    }
   
    fpw = fopen("dump.wav", "a+");
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
        write_wav_header(head); 
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
