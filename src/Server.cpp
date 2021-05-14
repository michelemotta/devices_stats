#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Server.h"
#include "Message.h"

Server::Server():
        fd_max(0),
        socket_listener(0),
        callback(NULL)
{

}

Server::~Server()
{
    
}

void Server::init(int port, std::function<void(std::string&)> received_data)
{
    if(NULL != received_data)
    {
        callback = received_data;
    }

    FD_ZERO(&master_fds);
    FD_ZERO(&read_fds);

    if((socket_listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("Failed to allocate socket!");
      std::exit(1);
    }

    const int reuse = 1;
    if(setsockopt(socket_listener, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
    {
      perror("Failed to set option for reusability!");
      std::exit(1);
    }

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(port);
    memset(&(my_addr.sin_zero), '\0', 8);
    if(bind(socket_listener, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
      perror("Failed to bind!");
      std::exit(1);
    }

    if(listen(socket_listener, 10) == -1)
    {
      perror("Failed to set listening socket!");
      std::exit(1);
    }

    FD_SET(socket_listener, &master_fds);

    fd_max = socket_listener;
    
}

void Server::listen_connections()
{
    read_fds = master_fds;

    std::cout << "Listening for connections" << std::endl;

    //Waiting only for incoming data and/or connections
    if(select((fd_max + 1), &read_fds, NULL, NULL, NULL) == -1)
    {
        perror("Error: select failed");
        std::exit(1);
    }

    std::cout << "Something happened" << std::endl;   

    for(int i = 0; i <= fd_max; i++) 
    {
        if(FD_ISSET(i, &read_fds))
        {
            if(i == socket_listener)
            {
                //New connection!
                new_connection(master_fds, socket_listener);
            }
            else
            {
                //Read incoming data
                read(master_fds, i);
            }
        }
    }
}

void Server::new_connection(fd_set& master, int& socket)
{
    int new_fd = 0;
    struct sockaddr_in remoteaddr;

    socklen_t addrlen = sizeof(remoteaddr);

    if((new_fd = accept(socket, (struct sockaddr *)&remoteaddr, &addrlen)) == -1)
    {
        perror("Failed to accept incoming connection!");
    }
    else
    {
        FD_SET(new_fd, &master);
        if (new_fd > fd_max)
        {
            fd_max = new_fd;
        }
        
        std::cout << "New connection from " << inet_ntoa(remoteaddr.sin_addr) <<
                     " with socket " << new_fd << std::endl;
    }
}

void Server::read(fd_set& master, int& socket)
{
    int read_bytes = 0;
    char buffer[256] = {0};

    if((read_bytes = recv(socket, buffer, sizeof(buffer), 0)) <= 0)
    {
        //Connection closed - Clean
        if (read_bytes == 0)
        {
            std::cout << "Socket " << socket << " hung up\n" << std::endl;
        }
        else
        {
            perror("Socket error!");
        }

        close(socket);

        FD_CLR(socket, &master);
    }
    else
    {
        const std::string response_message = "Data received. Thank you!\r\n";
        if (send(socket, response_message.c_str(), response_message.size(), 0) == -1)
        {
            perror("Error sending response to client!");
        }

        if(NULL != callback)
        {
            std::string buffer_str(buffer);
            callback(buffer_str);
        }

    }
}