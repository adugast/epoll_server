#include <stdio.h>
#include <unistd.h>

#include "epoll_server.h"

int epoll_server(int ip_addr, int port)
{
    int ret = -1;
    int sockfd = -1;

    sockfd = get_listening_socket(ip_addr, port);
    if (sockfd == -1) {
        return -1;
    }

    epoll_server_loop(sockfd);

    ret = close(sockfd);
    if (ret == -1) {
        perror("close()");
        return -1;
    }

    return 0;
}

int entry()
{
    epoll_server(0x7f000001, 9999);
    return 0;
}

int main(int argc, char *argv[])
{
    entry();
    return 0;
}
