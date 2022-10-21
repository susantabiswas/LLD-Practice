#ifndef EXACT_SPLIT_H
#define EXACT_SPLIT_H

#include <iostream>
#include "split_technique.h"
#include "../user.h"
#include <vector>
#include "../exceptions.h"
using namespace std;

class ExactSplit : SplitTechniqueBase {
public:
    void splitAmount(double amount, string payer_id, vector<User*>& participants,
        vector<double> share_to_pay) override {
        
        // check if the sum of total share to pay equals the total amount
        if(amount != accumulate(share_to_pay.begin(), share_to_pay.end(), 0))
            throw ShareNotEqualToTotal();

        if(participants.size() != share_to_pay.size())
            throw invalid_argument("Vector sizes are different");

        // all the participants owe the payee 'per_user-amt' money
        for(int i = 0; i < participants.size(); i++) {
            participants[i]->addUserOwed(payer_id, share_to_pay[i]);
        }
    }
};

#endif