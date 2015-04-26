#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv)
{
    int pipefd[2];
    pid_t cpid;
    char * buf;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    errno = 0;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        perror(sys_errlist[errno]);
        exit(EXIT_FAILURE);
    }

    errno = 0;
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        perror(sys_errlist[errno]);
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) { //child
        close(pipefd[1]);

        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1); //STDOUT_FILENO: int and no have buffer
        }

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } else { //parent
        close(pipefd[0]);
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
