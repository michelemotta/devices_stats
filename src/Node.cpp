#include <iostream>
#include <functional>

#include "Node.h"
#include "Server.h"
#include "Message.h"

Node::Node()
{

}

Node::~Node()
{
    
}

void Node::init(void)
{
    std::cout << "Hello! Node is ready to collect data..." << std::endl;
}

void Node::run(void)
{
    Server my_sample_server;
    my_sample_server.init(1234, std::bind(&Node::new_message, this, std::placeholders::_1));
    while(1)
    {
        my_sample_server.listen_connections();
    }
}

void Node::new_message(std::string& buffer)
{
    //New message could be handled by a new thread
    std::cout << buffer << std::endl;

    //Message message;
    //parser.validate_and_parse(message);
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());

    Message message(buffer, std::string());
    storage.store(message);
    storage.print_stats();
    //storage.print_id_stats();

}