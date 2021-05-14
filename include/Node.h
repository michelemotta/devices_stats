#ifndef __NODE__H
#define __NODE__H

#include <string>

#include "Storage.h"

class Node
{
public:
    Node();
    ~Node();

    void init(void);
    void run(void);
    void new_message(std::string& buffer);

private:
    Storage storage;

};

#endif