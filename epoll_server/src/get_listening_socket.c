#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

int get_listening_socket(int ip_addr, int port)
{
    int ret = -1;
    int sockfd = -1;

    // 1) Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return -1;
    }

    // 2) Bind
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(ip_addr);
    addr.sin_port = htons(port);

    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (ret == -1) {
        perror("bind()");
        close(sockfd);
        return -1;
    }

    // 3) Listen
    ret = listen(sockfd, 0);
    if (ret == -1) {
        perror("listen()");
        close(sockfd);
        return -1;
    }

    return sockfd;
}
