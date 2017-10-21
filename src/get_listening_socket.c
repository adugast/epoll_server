#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>


int get_listening_socket(int ip_addr, int port, int backlog)
{
    int ret = -1;
    int sockfd = -1;

    // 1) socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket()");
        return -1;
    }

    // 2) bind
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(ip_addr);

    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (ret == -1) {
        perror("bind()");
        close(sockfd);
        return -1;
    }

    // 3) listen
    ret = listen(sockfd, backlog);
    if (ret == -1) {
        perror("listen()");
        close(sockfd);
        return -1;
    }

    return sockfd;
}
