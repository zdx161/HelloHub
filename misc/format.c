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
    FILE * fp = NULL;

    if ((dp = opendir(argv[1])) == NULL)
    {
        printf("error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((dirp = readdir(dp)) != NULL ) {
        if (dirp->d_type == DT_REG) {
            snprintf(name, 256, "%s", dirp->d_name);
            
            fp = fopen(name, "r+");
            if (fp == NULL) {
                printf("error: %s\n", strerror(errno));
                goto OUT;
            }

            while (getline)
        }
            
    }

OUT:
    closedir(dp);
    exit(0);
}
