#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    FILE *from = NULL;
    FILE *to = NULL;
    char * line;
    int st;
    size_t num = 0;
    size_t size = 0;

    if (argc != 2) {
        printf("usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    from = fopen(argv[1], "r+");
    to = fopen("temp", "w+");

    if ((!from) || (!to)) {
        printf("error: open file failed.\n");

        if (to) {
            fclose(to);
            remove("temp");
        }

        if (from)
            fclose(from);

        exit(EXIT_FAILURE);
    }


    while ((size = getline(&line, &num, from)) != (size_t)-1) {
        if (size > 1) {
            for (st = size - 1; (st > 0) && (line[st - 1] == 0x20); st--) {
                line[st] = '\0';
            }
            line[st] = 0x0a;
        }

        fputs(line, to);
    }

    free(line);
    fclose(from);
    fclose(to);

    remove(argv[1]);
    rename("temp", argv[1]);

    exit(EXIT_SUCCESS);
}
