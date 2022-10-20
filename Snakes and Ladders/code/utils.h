#include <iostream>
#include <random>
using namespace std;

/*! Simple unique identity generator. Ideally one should use something 
    like UUID for this, but c++ doesnt have a native implementation for it.
*/
string getUniqueId(int len) {
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<int> dist{1, 256};

    string id;

    for(int i = 0; i < len; i++) 
        id += to_string(dist(gen));
    return id;
}
