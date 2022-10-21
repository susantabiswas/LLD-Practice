#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
using namespace std;

class NotFoundException: exception {
public:
    char* what() {
        return "Instance not found!!\n";
    }
};

class InstanceAlreadyExists: exception {
public:
    char* what() {
        return "Instance already exists!\n";
    }
};

class ShareNotEqualToTotal : exception {
public:
    char* what() {
        return "Sum of shares of each user isn't equal to total!\n";
    }
};
#endif