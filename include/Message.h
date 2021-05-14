#ifndef __MESSAGE__H
#define __MESSAGE__H

#include <string>

class Message
{
public:
    Message(){};
    Message(const std::string& device_id, const std::string& message_body)
    {
        device = device_id;
        body = message_body;
    };
    ~Message(){};

    void set_device_id(const std::string& device_id)
    {
        device = device_id;
    };

    void set_body(const std::string& message_body)
    {
        body = message_body;
    };

    const std::string& get_device_id()
    {
        return device;
    };

    const std::string& get_body()
    {
        return body;
    };

private:
    std::string device;
    std::string body;
};

#endif