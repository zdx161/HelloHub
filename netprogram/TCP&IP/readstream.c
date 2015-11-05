#include "cliserv.h"

int read_stream(int fd, char *ptr, int maxbytes)
{
    int nleft, nread;

    nleft = maxbytes;
    while (nleft > 0 ) {
        if ((nread = read(fd, ptr, nleft)) < 0)
           return nread;
        else if (nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }

    return (maxbytes - nread);
}

void err_sys(const char * str, ...)
{
    perror(str);
    exit(-1);
}

void err_quit(const char *str, ...)
{
    printf(str);
}


int main()
{
    char *str = "a = %d, b = %d\n";
    int a = 10, b = 20;
    printf(str,a,b);

    return 0;
}
