#ifndef SPLIT_TECHNIQUE_H
#define SPLIT_TECHNIQUE_H

#include <vector>
#include "../user.h"

enum SplitType { Equal, Exact, Percentage };

class SplitTechniqueBase {
public:
    virtual void splitAmount(double amount, string payer_id, 
        vector<User*>& participants, vector<double> share = {}) = 0;
};

#endif