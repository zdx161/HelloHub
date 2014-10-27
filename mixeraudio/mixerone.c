#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
   int pcmsize1 = 0;
   int pcmsize2 = 0;
   FILE *fp1 = NULL;
   FILE *fp2 = NULL;
   FILE *fout = NULL;

   fp1 = fopen(argv[1], "rb");
   if(fp1 == NULL){
       perror("fopen %s failed.\n", argv[1]);
       exit(EXIT_FAILURE);
   }

   fp2 = fopen(argv[2], "rb");
   if(fp1 == NULL){
       perror("fopen %s failed.\n", argv[2]);
       fclose(fp1);
       exit(EXIT_FAILURE);
   }

   fout = fopen("mixer.pcm", "wb");
   if(fp1 == NULL){
       perror("fopen mixer.pcm failed.\n");
       fclose(fp2);
       exit(EXIT_FAILURE);
   }

   int c = 0;
   unsigned int data = 0;
   unsigned int data2 = 'd' | 'a' << 8 | 't' << 16 | 'a' << 24
   int i = 0;
   int b = 0;
   while((c = fgetc(fp1)) != EOF){
       data = (data << 8) | (c & 0xff);
       if(i == 1){
           pcmsize1 = (pcmsize1 << 8) | (c & 0xff);
       }
       if(data == data2)
           i = 1;
   }

   

    fclose(fp1);
    fclose(fp2);
    fclose(fout);
    return 0;
}
