#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>

#include "epoll_server.h"

#define MAX_EVENTS 10

static int set_nonblocking(int sockfd)
{
    int flags = -1;

    flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("get fcntl()");
        return -1;
    }

    flags |= O_NONBLOCK;

    if (fcntl(sockfd, F_SETFL, flags) == -1) {
        perror("set fcntl()");
        return -1;
    }

    return 0;
}

int epoll_server_loop(int sockfd)
{
    int ret = -1;

    // epoll_loop
    struct epoll_event evt, events[MAX_EVENTS];
    int epollfd = -1;
    int nfds = -1;
    int i = 0;

    // 1) epoll_create
    epollfd = epoll_create(1);
    if (epollfd == -1) {
        perror("epoll_create()");
        return -1;
    }

    // 2) Epoll ctl
    evt.events = EPOLLIN;
    evt.data.fd = sockfd;

    ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &evt);
    if (ret == -1) {
        perror("epoll_ctl()");
        close(sockfd);
        close(epollfd);
        return -1;
    }

    int cli_fd = -1;

    for (;;) {

        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait()");
            close(sockfd);
            close(epollfd);
            return -1;
        }

        for (i = 0; i < nfds; i++) {
            if (events[i].data.fd == sockfd) {
                cli_fd = accept(sockfd, NULL, NULL);
                if (cli_fd == -1) {
                    perror("accept()");
                    close(sockfd);
                    return -1;
                } else {
                    printf("client[%d]:connected\n", cli_fd);
                }

                set_nonblocking(cli_fd);

                evt.events = EPOLLIN | EPOLLET;
                evt.data.fd = cli_fd;
                ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, cli_fd, &evt);
                if (ret == -1) {
                    perror("epoll_ctl()");
                    return -1;
                }

            } else {

                char buffer[256] = {0};
                ssize_t size_recv = 0;

                size_recv = recv(events[i].data.fd, buffer, 255, 0);
                if (size_recv < 1) {
                    printf("client[%d]:disconnected\n", events[i].data.fd);
                    close(events[i].data.fd);
                } else {
                    buffer[size_recv - 1] = '\0';
                    printf("[%d]buffer:[%s]\n", events[i].data.fd, buffer);
                }
            }
        }
    }

    return 0;
}

