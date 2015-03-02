#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
   unsigned int pcmsize1 = 0;
   unsigned int pcmsize2 = 0;
   FILE *fp1 = NULL;
   FILE *fp2 = NULL;
   FILE *fout = NULL;

   fp1 = fopen(argv[1], "rb");
   if(fp1 == NULL){
       printf("fopen %s failed.\n", argv[1]);
       exit(EXIT_FAILURE);
   }

   fp2 = fopen(argv[2], "rb");
   if(fp1 == NULL){
       printf("fopen %s failed.\n", argv[2]);
       fclose(fp1);
       exit(EXIT_FAILURE);
   }

   fout = fopen("mixer.pcm", "wb");
   if(fp1 == NULL){
       printf("fopen mixer.pcm failed.\n");
       fclose(fp2);
       exit(EXIT_FAILURE);
   }

   int c = 0;
   unsigned int data = 0;
   unsigned int data2 = 'd' | 'a' << 8 | 't' << 16 | 'a' << 24;
   unsigned int data3 = 'd' << 24 | 'a' << 16 | 't' << 8 | 'a';
   int i = 0;
   int b = 0;

    //printf("word is: %d\n", getw(fp1));

   while((c = fgetc(fp1)) != EOF){
       data = (data << 8) | (c & 0xff);
       fputc(c, fout);
       if(i == 1){
           pcmsize1 = pcmsize1 | ((((unsigned int)c) & 0xff) << (8 * b));
           b++;
       }

       if(data == data2 || data == data3)
           i = 1;
       if(b == 4)
           break;
   }

   printf("pcmsize1: %d\n", pcmsize1);
   
   i = 0;
   b = 0;
   c = 0;
   while((c = fgetc(fp2)) != EOF){
       data = (data << 8) | (c & 0xff);
       if(i == 1){
           pcmsize2 = pcmsize2 | ((((unsigned int)c) & 0xff) << (8 * b));
           b++;
       }

       if(data == data2 || data == data3)
           i = 1;
       if(b == 4)
           break;
   }

   printf("pcmsize2: %d\n", pcmsize2);
    
   short sample1 = 0;
   short sample2 = 0;
   while(1){
   int ret1 = fread(&sample1, sizeof(short), 1, fp1);
   int ret2 = fread(&sample2, sizeof(short), 1, fp2);
       if(ret1 > 0 && ret2 > 0 ){
           short sample =(short)((sample1 + sample2) - (sample1 * sample2 >> 0x10));            
           if(sample > 32767)
               sample = 32767;
           else if(sample < -32768)
               sample = -32768;
           fwrite(&sample, 2, 1, fout);

       }
       else
           break;
   }
#if 0
   int sample1 = 0;
   int sample2 = 0;
   b = 0;
   while((c = fgetc(fp1)) != EOF){
       int c1 = fgetc(fp2);
       sample1 = sample1 | ((c & 0xff) << (8 * b));
       sample2 = sample2 | ((c1 & 0xff) << (8 * b));
       b++;
       if(b == 2){
           b = 0;
           short sample = 0;
           sample =(short)sample1;
#if 0
           if(sample1 < 0 && sample2 < 0){
               sample = (short)(sample1+sample2-(sample1*sample2/(-(pow(2,16-1)-1))));
           }
           else
               sample = (short)(sample1+sample2-(sample1*sample2/(pow(2,16-1)-1)));
#endif
         fwrite((char*)(&sample), 1, 1,fout);
         fwrite((char*)(&sample + 1), 1, 1, fout);
                
#if 0
           short sampleout = 0;
           int sample = 0;
           sample = (sample1 + sample2) - (sample1 * sample2 >> 0x10);            
           if(sample > 32767)
               sampleout = 32767;
           else if(sample < -32768)
               sampleout = -32768;
           else
               sampleout = (short) sample;
           //fwrite((char*)(&sample), 2, 2, fout);
           char sd = (char)(sampleout & 0xff);
           fwrite(&sd, 1, 1, fout);
           sd = (char)((sampleout >> 8) | 0xff);
           fwrite(&sd, 1, 1, fout);
           sample1 = sample2 = 0;
#endif
       }
   }
#endif

    fclose(fp1);
    fclose(fp2);
    fclose(fout);
    return 0;
}
