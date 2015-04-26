#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAXLINE 1024

void client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    char buff[MAXLINE];

    /* read pathname */
    fgets(buff, MAXLINE, stdin);
    len = strlen(buff);
    if (buff[len - 1] == '\n')
        len--;

    /* write pathname to IPC channel */
    write(writefd, buff, len);

    /* read from IPC, write to standard output */
    while ((n = read(readfd, buff, MAXLINE)) > 0)
        write(STDOUT_FILENO, buff, n);
}

void server(int readfd, int writefd)
{
    int fd;
    ssize_t n;
    char buff[MAXLINE + 1];

    /* read pathname from IPC channel */
    if ((n = read(readfd, buff, MAXLINE)) == 0) {
        printf("end-of-file while reading pathname");
        exit(0);
    }

    buff[n] = '\0';   /* null terminate pathname */

    if ((fd = open(buff, O_RDONLY)) < 0) {
        /* error: must tell client */
        snprintf(buff + n, sizeof(buff) - n, ": cann't open, %s\n", strerror(errno));
        n = strlen(buff);
        write(writefd, buff, n);
    } else {
        /* open succeeded: copy file to IPC channel */
        while((n = read(fd, buff, MAXLINE)) > 0)
            write(writefd, buff, n);

        close(fd);
    }
}
