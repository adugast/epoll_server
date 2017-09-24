#ifndef __EPOLL_SERVER_H__
#define __EPOLL_SERVER_H__

int get_listening_socket(int ip_addr, int port, int backlog);
int epoll_server_loop(int sockfd);

#endif /* __EPOLL_SERVER_H__ */
