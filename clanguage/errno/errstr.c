#include <stdio.h>
#include <string.h>
#include <errno.h>


int main()
{
    int i = 1;
    char *str = NULL;
    for (; /*errno = i,*/ i < 256; i++) {
        printf("error(%d): %s\n", i, str = (strstr(str = strerror(i),"Unknow") == NULL ? str : ""));
        if (str == "")
            break;
        //perror("");
    }

    return 0;
}
