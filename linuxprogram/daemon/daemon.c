#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>

#define DAEMON_NAME "mydaemon"

#define RUN_AS_USER "daemon"

//#define EXIT_SUCCESS 0
//#define EXIT_FAILURE 0

static void child_handler(int signum)
{
    switch(signum) {
        case SIGALRM:
            exit(EXIT_FAILURE);
            break;
        case SIGUSR1:
            exit(EXIT_SUCCESS);
            break;
        case SIGCHLD:
            exit(EXIT_FAILURE);
            break;
    }
}

static void daemonize(const char *lockfile)
{
    pid_t pid, sid, parent;
    int lfp = -1;

    if(getppid() == 1)
        return;

    if(lockfile && lockfile[0]) {
        lfp = open(lockfile, O_RDWR | O_CREAT, 0640);
        if (lfp < 0) {
            syslog(LOG_ERR, "unable to create lock file %s, code = %d(%s)", lockfile, errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    if (getuid() == 0 || geteuid() == 0) {
        struct passwd * pw = getpwnam(RUN_AS_USER);
        if (pw) {
            syslog(LOG_NOTICE, "setting user to " RUN_AS_USER);
            setuid(pw->pw_uid);
        }
    }

    signal(SIGCHLD, child_handler);
    signal(SIGUSR1, child_handler);
    signal(SIGALRM, child_handler);

    //the first step: Fork the parent process
    pid = fork();
    if (pid < 0) {
        syslog(LOG_ERR, "unable to fork daemon, code = %d(%s)", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        alarm(2);
        pause();

        exit(EXIT_FAILURE);
    }

    parent = getppid();

    signal(SIGCHLD, SIG_DFL);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    signal(SIGTERM, SIG_DFL);

    //the second step: changing the file mode mask
    umask(0);

    //the third step: create a unique session id
    sid = setsid();
    if (sid < 0) {
        syslog(LOG_ERR, "unable to create a new session, code = %d (%s)", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //the fourth step: changing the working directory
    if ((chdir("/")) < 0) {
        syslog(LOG_ERR, "unable to change directory to %s, code = %d(%s)", "/", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //the fifth step: closing standard file descriptors
    freopen("/dev/null", "r", stdin);
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);

    kill(parent, SIGUSR1);
}


int main(int argc, char *argv)
{
    openlog(DAEMON_NAME, LOG_PID, LOG_LOCAL5);
    syslog(LOG_INFO, "starting");

    daemonize("/var/lock/subsys/" DAEMON_NAME);

    syslog(LOG_NOTICE, "terminated");
    closelog();

    return 0;
}
