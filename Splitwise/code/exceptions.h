#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
using namespace std;

class NotFoundException: exception {
public:
    char* what() {
        return "Instance not found!!";
    }
};

class InstanceAlreadyExists: exception {
public:
    char* what() {
        return "Instance already exists!";
    }
};

#endif