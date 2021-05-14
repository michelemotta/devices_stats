#ifndef __SERVER__H
#define __SERVER__H

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>


class Server
{
public:
    Server();
    ~Server();

    void init(int port);
    void listen_connections();
private:
    const static int PORT = 1234;

    fd_set master_fds;
    fd_set read_fds;

    int fdmax;
    int socket_listener;

    void new_connection(fd_set& master, int& socket);
    void read(fd_set& master, int& socket);

};

#endif