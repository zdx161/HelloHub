#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <unistd.h>


#define MSG_R 0400
#define MSG_W 0200

#define SVMSG_MODE (MSG_R | MSG_W | MSG_R >> 3 | MSG_W >> 6)

int main(int argc, char ** argv)
{
    struct stat fstat;

    if (argc != 2) {
        printf("usage: ftok <pathname>");
        exit(EXIT_FAILURE);
    }

    stat(argv[1], &fstat);

    printf("st_dev: %lx, st_ino: %lx, key: %x\n",(unsigned long)fstat.st_dev, (unsigned long)fstat.st_ino, ftok(argv[1], 0x57));

    /////////////////////////////////////slot/////////////////////////////
    int i, msqid;

    for (i = 0; i < 10; i++) {
        msqid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
        printf("msqid = %d\n", msqid);

        msgctl(msqid, IPC_RMID, NULL);
    }


    return 0;
}
