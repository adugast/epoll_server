#########
# CMAKE #
#########

cmake_minimum_required(VERSION 2.8.3)

project(epoll_server)

## Target
add_executable(
    epoll_server
    src/main.c
    src/epoll_server.c
    src/get_listening_socket.c
)
