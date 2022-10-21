#ifndef PERCENTAGE_SPLIT_H
#define PERCENTAGE_SPLIT_H

#include <iostream>
#include "split_technique.h"
#include "../user.h"
#include "../exceptions.h"
#include <vector>
using namespace std;

class PercentageSplit : SplitTechniqueBase {
public:
    void splitAmount(double amount, string payer_id, vector<User*>& participants,
        vector<double> share_percent) override {
       
        // check if the sum of total share percentages equals 100
        if(100.0 != accumulate(share_percent.begin(), share_percent.end(), 0))
            throw ShareNotEqualToTotal();

        if(participants.size() != share_percent.size())
            throw invalid_argument("Vector sizes are different");

        // all the participants owe the payee 'per_user-amt' money
        for(int i = 0; i < participants.size(); i++) {
            participants[i]->addUserOwed(payer_id, amount * share_percent[i]);
        }
    }
};

#endif