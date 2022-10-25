#ifndef SPLIT_TECHNIQUE_H
#define SPLIT_TECHNIQUE_H

#include <vector>
#include "../user.h"

/**
 * @brief Enum that represents the various splitting techniques.
 * 
 */
enum SplitType { Equal, Exact, Percentage };

/**
 * @brief Base class for implementing split technique
 * 
 */
class SplitTechniqueBase {
public:
    virtual void splitAmount(double amount, User* payer, 
        vector<User*>& participants, vector<double> share = {}) = 0;
};

#endif