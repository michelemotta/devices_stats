#ifndef __NODE__H
#define __NODE__H

#include <string>

class Node
{
public:
    Node();
    ~Node();

    void init(void);
    void run(void);
    void new_message(std::string);

};

#endif