#ifndef __SERVER__H
#define __SERVER__H

#include <sys/types.h>
#include <functional>

class Server
{
public:
    Server();
    ~Server();

    void init(int port, std::function<void(std::string&)> received_data);
    void listen_connections();

private:
    fd_set master_fds;
    fd_set read_fds;

    int fd_max;
    int socket_listener;

    std::function<void(std::string&)> callback;

    void new_connection(fd_set& master, int& socket);
    void read(fd_set& master, int& socket);

};

#endif