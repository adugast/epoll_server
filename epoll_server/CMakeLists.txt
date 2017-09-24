#########
# CMAKE #
#########

cmake_minimum_required(VERSION 2.8.3)

project(epoll_server)

## Target
add_executable(server src/main.c src/get_listening_socket.c)
