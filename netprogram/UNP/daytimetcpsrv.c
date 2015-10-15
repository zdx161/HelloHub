#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>


int main()
{
    int listenfd, acceptfd, n;
    struct sockaddr_in serv_addr;
    char senddata[256];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("ERROR: socket failed.");
        exit(1);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(13);
    
    n = bind(listenfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0) {
        perror("ERROR: bind failed.");
        exit(1);
    }

    listen(listenfd, 5);
    
    while (1) {
        acceptfd = accept(listenfd, NULL, NULL);
        time_t ticks = time(NULL);
        snprintf(senddata, sizeof(senddata), "%.24s\r\n", ctime(&ticks));
        write(acceptfd, senddata, strlen(senddata));
        close(acceptfd);
    }
}
