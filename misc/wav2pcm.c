#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv)
{
    if (argc != 2) {
        printf("usage: exe file\n");
        exit(EXIT_FAILURE);
    }

    FILE * in = NULL;
    FILE * out = NULL;
    char * outname = strdup(argv[1]);
    char * lindex = rindex(outname, '.');
    snprintf(lindex + 1, 4, "%s", "pcm");
    printf("outname: %s\n", outname);

    in = fopen(argv[1], "rb");
    out = fopen(outname, "wb");

    if (in == NULL || out == NULL) {
        printf("open file failed.\n");
        goto err;
    }

#if 1
    int c = 0;
    int data = 0;
    while((c = getc(in)) != EOF){
        data = (data << 8) | (c & 0xFF);
        if (data == *((int*)"atad")){ //note endian: "data" is failed.
            for (c = 0; c < 4; c++)
                getc(in);
            break;
        }
    }

    while((c = getc(in)) != EOF){
        putc(c, out);
    }
#else
    printf("data: 0x%x == %d\n", *((int*)"data"), *((int*)"data"));
#endif

err:
    if(in != NULL)
        fclose(in);
    if(out != NULL)
        fclose(out);
    if(outname != NULL)
        free(outname);

    return 0;
}
