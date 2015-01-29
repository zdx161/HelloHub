/** ******************************************
 **    ctrl + C == kill -s 2 pid
 **    accept signal and do with process
 ** *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int exitsig = 0;

void * signal_handle(int signum)
{
    printf("signum: %d\n", signum);
    exitsig = 1;
}

int main()
{
    while(1) {
        printf("sleep 1000 us\n");
        usleep(1000);
        signal(SIGINT, signal_handle);
        if(exitsig == 1) {
            break;
            exitsig = 0;
        }
    }

    printf("process exit: pid: %d\n", getpid());
    return 0;
}
