#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

struct Resource {
    int id;
    std::string name;
    std::string type;
    bool available;
};

#endif