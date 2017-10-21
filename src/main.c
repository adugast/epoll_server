#include "epoll_server.h"


int entry()
{
    epoll_server(0x7f000001, 9999, 10);
    return 0;
}


int main(int argc, char *argv[])
{
    entry();
    return 0;
}
