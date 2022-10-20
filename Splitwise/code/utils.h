#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
using namespace std;

/**
 * @brief Generates an Unique Id string
 * 
 * @param len : No. of unique parts used.   
 * @return id string 
 */
string getUniqueId(int len) {
    mt19937 mt;
    uniform_int_distribution<int> dist{1, 256};

    string id;
    for(int i = 0; i < len; i++)
        id += to_string(dist(mt));
    return id;
}

#endif