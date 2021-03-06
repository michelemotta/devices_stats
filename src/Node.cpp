#include <iostream>
#include <functional>

#include "Node.h"
#include "Server.h"
#include "Message.h"

Node::Node():
    storage(NULL)
{

}

Node::~Node()
{
    
}

void Node::init(Storage* const store)
{
    std::cout << "Hello! Node is ready to collect data..." << std::endl;

    if(NULL != store)
    {
        storage = store;
    }
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
    //std::cout << buffer << std::endl;

    //Remove end of line if any
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());

    Message message;
    if(Validator::VALID_MESSAGE == validator.validate_and_parse(buffer, message))
    {
        if(NULL != storage)
        {
            storage->store(message);
            storage->print_stats();
            //Print sorted data
            //storage.print_id_stats();
        }
    }
    else
    {
        std::cout << "Wrong formatted message received. Discarded." << std::endl;
    }

}