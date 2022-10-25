#ifndef EQUAL_SPLIT_H
#define EQUAL_SPLIT_H

#include <iostream>
#include "split_technique.h"
#include "../user.h"
#include <vector>
using namespace std;

/**
 * @brief Implementation for Equal amount split technique
 * 
 */
class EqualSplit : public SplitTechniqueBase {
public:
    /**
     * @brief Splits the amount into equal parts amongst the participants       
     * 
     * @param amount : total amount involved
     * @param payer : User who paid for the expense
     * @param participants : Users involved in the expense, includes the payer as well
     * @param share : this is not needed for equal split
     */
    void splitAmount(double amount, User* payer, vector<User*>& participants, 
        vector<double> share = {}) override {
        
        string payer_id = payer->getUserId();

        int num_users = participants.size();
        double per_user_amt = amount / num_users;

        cout << "Payer " << payer->getName() << "(" << payer->getUserId() << ") 's share: " 
            << amount - ((participants.size() - 1) * per_user_amt) << endl;
        
        // all the participants owe the payee 'per_user-amt' money
        for(auto user: participants) {
            if(user == payer) 
                continue;

            user->addUserOwed(payer_id, per_user_amt);
            cout << user->getName() << "(" << user->getUserId() << ") owes " << per_user_amt << 
                " to " << payer->getName() << "(" << user->getUserId() << ")\n";
        }
    }
};

#endif