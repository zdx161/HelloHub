#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>


int main(int argc, char * argv[])
{
    DIR * dp;
    struct dirent * dirp;
    char name[256] = {0};
    char *line = NULL;
    FILE * from = NULL;
    FILE * to = NULL;
    size_t size, num;
    int st;


    if (argc != 2) {
        printf("usage: %s directory\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((dp = opendir(argv[1])) == NULL)
    {
        printf("error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((dirp = readdir(dp)) != NULL ) {
        if (dirp->d_type == DT_REG) {
            snprintf(name, 256, "%s", dirp->d_name);
            printf("%s\n", name);

            errno = 0;
            from = fopen(name, "r+");
            to = fopen("temp", "w+");
            if (from  == NULL || to == NULL) {
                printf("error: %s\n", strerror(errno));
                break;
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

            fclose(from);
            from = NULL;

            fclose(to);
            to = NULL;

            remove(name);
            rename("temp", name);
        }
    }

    if(from)
        fclose(from);

    if(to)
        fclose(to);

    if(line)
        free(line);

    closedir(dp);
    exit(0);
}
