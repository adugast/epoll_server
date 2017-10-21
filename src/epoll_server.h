#ifndef __EPOLL_SERVER_H__
#define __EPOLL_SERVER_H__

int epoll_server(int ip_addr, int port, int backlog);
int get_listening_socket(int ip_addr, int port, int backlog);

#endif /* __EPOLL_SERVER_H__ */
