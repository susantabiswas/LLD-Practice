#ifndef PERCENTAGE_SPLIT_H
#define PERCENTAGE_SPLIT_H

#include <iostream>
#include "split_technique.h"
#include "../user.h"
#include "../exceptions.h"
#include <vector>
#include <limits>
using namespace std;

/**
 * @brief Represents percentage split technique.
 * 
 */
class PercentageSplit : SplitTechniqueBase {
public:
    /**
     * @brief Splits the amount into % parts amongst the participants       
     * 
     * @param amount : total amount involved
     * @param payer : User who paid for the expense
     * @param participants : Users involved in the expense, includes the payer as well
     * @param share : exact amount % corresponding to each user's contribution in the expense
     */
    void splitAmount(double amount, User* payer, vector<User*>& participants,
        vector<double> share_percent) override {
       
        string payer_id = payer->getUserId();
        double total_share = (double)accumulate(share_percent.begin(), share_percent.end(), 0.0);
        
        // check if the sum of total share percentages equals 100
        // Comparing float values with == can give incorrect results,
        // instead we can check if the difference is less than the smallest value
        // that can be represented by c++
        if((total_share - 1.0) > numeric_limits<double>::epsilon())
            throw ShareNotEqualToTotal();

        if(participants.size() != share_percent.size())
            throw invalid_argument("Vector sizes are different\n");
        
        // all the participants owe the payee 'per_user-amt' money
        for(int i = 0; i < participants.size(); i++) {
            User* user = participants[i];
            
            if(user == payer) {
                cout << "Payer " << payer->getName() << "(" << payer->getUserId() << ") 's share: " 
                    << amount * share_percent[i] << endl;
                continue;
            }
            cout << user->getName() << "(" << user->getUserId() << ")'s share: " << amount * share_percent[i] << endl;
            
            participants[i]->addUserOwed(payer_id, amount * share_percent[i]);
        }
    }
};

#endif