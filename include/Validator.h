#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#include <string>
#include "Message.h"

class Validator
{
public:
    typedef enum
    {
        VALID_MESSAGE,
        BAD_MESSAGE
    }Result;

    Validator(){};
    ~Validator(){};

    Result validate_and_parse(const std::string& buffer, Message& message)
    {
        Result ret = BAD_MESSAGE;
        std::size_t separator = buffer.find(":", 0);

        if(separator != std::string::npos)
        {
            message.set_device_id(buffer.substr(0, separator));
            message.set_body(buffer.substr((separator+1), std::string::npos));

            ret = VALID_MESSAGE;
        }

        return ret;
    }

};

#endif