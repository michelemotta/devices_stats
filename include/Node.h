#ifndef __NODE__H
#define __NODE__H

#include <string>

#include "Storage.h"
#include "Validator.h"

class Node
{
public:
    Node();
    ~Node();

    void init(Storage* const store);
    void run(void);
    void new_message(std::string& buffer);

private:
    Storage* storage;
    Validator validator;

};

#endif