#ifndef EXACT_SPLIT_H
#define EXACT_SPLIT_H

#include <iostream>
#include "split_technique.h"
#include "../user.h"
#include <vector>
#include "../exceptions.h"
using namespace std;

/**
 * @brief Represents exact split technique
 * 
 */
class ExactSplit : SplitTechniqueBase {
public:
    /**
     * @brief Splits the amount into exact parts amongst the participants       
     * 
     * @param amount : total amount involved
     * @param payer : User who paid for the expense
     * @param participants : Users involved in the expense, includes the payer as well
     * @param share : exact amount corresponding to each user's contribution in the expense
     */
    void splitAmount(double amount, User* payer, vector<User*>& participants,
        vector<double> share_to_pay) override {
        
        string payer_id = payer->getUserId();
        // check if the sum of total share to pay equals the total amount
        if(amount != accumulate(share_to_pay.begin(), share_to_pay.end(), 0))
            throw ShareNotEqualToTotal();

        if(participants.size() != share_to_pay.size())
            throw invalid_argument("Vector sizes are different");


        // all the participants owe the payee 'per_user-amt' money
        for(int i = 0; i < participants.size(); i++) {
            User* user = participants[i];
            
            if(user == payer) {
                cout << "Payer " << payer->getName() << "(" << payer->getUserId() << ") 's share: " 
                    << share_to_pay[i] << endl;
                continue;
            }
            cout << user->getName() << "(" << user->getUserId() << ")'s share: " << share_to_pay[i] << endl;
            participants[i]->addUserOwed(payer_id, share_to_pay[i]);
        }
    }
};

#endif