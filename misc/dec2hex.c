#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char ** argv)
{
    if (argc < 2) {
        printf("usage: dec2hex num\n");
        exit(0);
    }

    int d = atoi(argv[1]);
    int i;
    char *str = NULL;
    str = (char*)malloc(INT_MAX/16 + 2);
    if (str == NULL){
        printf("malloc failed.");
        exit(EXIT_FAILURE);
    }

    printf("%d = ", d);
    for (i = 0; d > 0; i++) {
        sprintf(str+i, "%x", d % 16);
        d /= 16;
    }

    for (; i >= 0; i--) {
        printf("%c", str[i]);
    }

    printf("\n");

    free(str);
    exit(0);
}
