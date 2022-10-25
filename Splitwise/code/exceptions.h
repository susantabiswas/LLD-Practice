#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
/**
 * @brief Custom errors for the code
 * 
 */

#include <iostream>
using namespace std;

class NotFoundException: exception {
public:
    char* what() {
        return "[Exception] Instance not found!!\n";
    }
};

class InstanceAlreadyExists: exception {
public:
    char* what() {
        return "[Exception] Instance already exists!\n";
    }
};

class ShareNotEqualToTotal : exception {
public:
    char* what() {
        return "[Exception] Sum of shares of each user isn't equal to total!\n";
    }
};
#endif