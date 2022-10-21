#ifndef EQUAL_SPLIT_H
#define EQUAL_SPLIT_H

#include <iostream>
#include "split_technique.h"
#include "../user.h"
#include <vector>
using namespace std;

class EqualSplit : public SplitTechniqueBase {
public:
    void splitAmount(double amount, string payer_id, vector<User*>& participants, 
        vector<double> share = {}) override {

        int num_users = participants.size();
        double per_user_amt = amount / num_users;

        // all the participants owe the payee 'per_user-amt' money
        for(auto user: participants) {
            user->addUserOwed(payer_id, per_user_amt);
        }
    }
};

#endif