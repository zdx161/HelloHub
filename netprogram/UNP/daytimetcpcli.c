#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>

int main(int argc, char ** argv)
{
    int sockfd, n;
    char recvline[256];
    struct sockaddr_in serv_addr;
    
    if (argc < 2) {
        printf("usage: %s hostname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR: open socket failed.");
        exit(1);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(13);

    n = inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
    if (n < 0) {
        perror("ERROR: inet_pton failed.");
        exit(1);
    }
    
    n = connect(sockfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0) {
        perror("ERROR: connect failed.");
        exit(1);
    }

    while ((n = read(sockfd, recvline, 255)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF) {
            perror("ERROR: fputs failed.");
            exit(1);
        }
    }

    if (n < 0) {
        perror("ERROR: read failed.");
        exit(1);
    }
    
    exit(0);
}
