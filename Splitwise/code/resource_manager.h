#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <unordered_map>
#include "exceptions.h"
using namespace std;

/**
 * @brief Manager that manages T type of resource. Supports get, add, delete operations.
 * 
 * @tparam T : Kind of resource
 */
template <typename T>
class ResourceManager {
private:
    unordered_map<string, T*> instances_;
public:
    ResourceManager() {
        instances_ = unordered_map<string, T*>();
        instances_.clear();
    }

    T* getInstance(string id) {
        // check if instance exists
        if(!isPresent(id))
            throw NotFoundException();
        return instances_[id];
    }

    void addInstance(string id, T* instance) {
        // check if already present with the same id
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

    unordered_map<string, T*> getAllInstances() { return this->instances_; }

    bool isPresent(string& id) { 
        return this->instances_.count(id); 
    }
};
#endif