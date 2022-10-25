#ifndef SPLIT_CONTROLLER_H
#define SPLIT_CONTROLLER_H

#include "equal_split.h"
#include "exact_split.h"
#include "percentage_split.h"

using namespace std;

/**
 * @brief Controller that decides the selection of split technique.
 * 
 */
class SplitController {
private:
    EqualSplit equal_split_;
    ExactSplit exact_split_;
    PercentageSplit percentage_split_;

public:
    SplitController() {}

    /**
     * @brief Selects the expense splitting technique based on the split type.       
     * 
     * @param amount : total amount involved
     * @param payer : User who paid for the expense
     * @param participants : Users involved in the expense, includes the payer as well
     * @param share : exact amount % corresponding to each user's contribution in the expense
     */
    void splitAmount(SplitType split_type, double amount, User* payer, 
        vector<User*>& participants, vector<double> share = {}) {
        
        cout << "Expense split details\n";
        cout << "Payer: " << payer->getName() << " (" << payer->getUserId() << ")" << endl;
        switch(split_type) {
            case Equal:
                cout << "Split type: Equal\n";
                equal_split_.splitAmount(amount, payer, participants, share);
                break;
            case Exact:
                cout << "Split type: Exact\n";
                exact_split_.splitAmount(amount, payer, participants, share);
                break;
            case Percentage:
                cout << "Split type: Percentage\n";
                percentage_split_.splitAmount(amount, payer, participants, share);
                break;
            default:
                throw invalid_argument("Invalid Split type!!\n");
        }
    }
};

#endif