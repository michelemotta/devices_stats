#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <vector>
#include <algorithm>
#include <iostream>
#include "Message.h"

class Item
{
public:
    Item(const std::string name):cont(1), id(name){};
    ~Item(){};

    bool operator <(const Item &b) const
    {
        return (id < b.id);
    }

    bool operator ==(const Item &b) const
    {
        return (id == b.id);
    }

    void new_item()
    {
        cont++;
    };

    const std::string get_id()
    {
        return id;
    };

    const int get_count()
    {
        return cont;
    }

private:
    std::string id;
    int cont;
};

class Storage
{
public:
    Storage(){};
    ~Storage(){};

    void store(Message& message)
    {
        Item item(message.get_device_id());

        std::vector<Item>::iterator it = std::find(collection.begin(), collection.end(), item);

        if(it != collection.end())
        {
            it->new_item();
        }
        else
        {
            collection.push_back(item);
        }
    };

    void print_stats()
    {
        std::cout << "Stats summary" << std::endl;
        std::cout << "Device ID : Tot messages" << std::endl;
        std::cout << std::string(20, '-') << std::endl;

        for(std::vector<Item>::iterator it = collection.begin(); it < collection.end(); ++it)
        {
            std::cout << it->get_id() << " : " << it->get_count() <<std::endl;
        }

        std::cout << std::string(20, '-') << std::endl << std::endl;
    };

private:
    std::vector<Item> collection;

};

#endif