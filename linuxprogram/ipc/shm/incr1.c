#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "config.h"

#define SEM_NAME "mysem"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int count = 0;

int main(int argc, char ** argv)
{
    int i, nloop;
    sem_t * mutex;
    if (argc != 2) {
        printf("usage: incr1 <#loops>\n");
        exit(EXIT_FAILURE);
    }

    nloop = atol(argv[1]);

    mutex = sem_open(px_ipc_name(SEM_NAME), O_CREAT|O_EXCL, FILE_MODE, 1);
    sem_unlink(px_ipc_name(SEM_NAME));
    setbuf(stdout, NULL); /* stdout is unbuffered */

    if (fork() == 0) {
        for (i = 0; i < nloop; i++) {
            sem_wait(mutex);
            printf("child: %d\n", count++);
            sem_post(mutex);
        }
        exit(0);
    }

    for (i = 0; i < nloop; i++) {
        sem_wait(mutex);
        printf("parent: %d\n", count++);
        sem_post(mutex);
    }
    exit(0);
}
