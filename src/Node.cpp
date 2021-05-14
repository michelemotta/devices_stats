#include <iostream>

#include "Node.h"
#include "Server.h"

Node::Node()
{

}

Node::~Node()
{
    
}

void Node::init(void)
{
    std::cout << "Hello" << std::endl;
}

void Node::run(void)
{
    Server my_sample_server;
    my_sample_server.init(1234);
    while(1)
    {
        my_sample_server.listen_connections();   
    }
}

void Node::new_message(std::string)
{
    
}