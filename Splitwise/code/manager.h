#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <unordered_map>
#include "exceptions.h"
using namespace std;

template <typename T>
class Manager {
private:
    unordered_map<string, T*> instances_;
public:
    T* getInstance(string id) {
        // check if instance exists
        if(!isPresent(id))
            throw NotFoundException();
        return instances_[id];
    }

    void addInstance(string id, T* instance) {
        // check if already present
        if(isPresent(id))
            throw InstanceAlreadyExists();
        instances_[id] = instance;
    }

    void removeInstance(string id) {
        // check if instance exists
        if(!isPresent(id))
            throw NotFoundException();
        instances_.erase(id);
    }

    bool isPresent(string id) { return this->instances_.count(id); }
};
#endif