#ifndef SPLIT_CONTROLLER_H
#define SPLIT_CONTROLLER_H

#include "equal_split.h"
#include "exact_split.h"
#include "percentage_split.h"

using namespace std;

class SplitController {
private:
    EqualSplit equal_split_;
    ExactSplit exact_split_;
    PercentageSplit percentage_split_;

public:
    SplitController(EqualSplit equal_split, 
        ExactSplit exact_split, 
        PercentageSplit percentage_split) 
        : equal_split_(equal_split), exact_split_(exact_split), percentage_split_(percentage_split) {}

    void splitAmount(SplitType split_type, double amount, string payer_id, 
        vector<User*>& participants, vector<double> share = {}) {
        
        switch(split_type) {
            case Equal:
                equal_split_.splitAmount(amount, payer_id, participants, share);
                break;
            case Exact:
                exact_split_.splitAmount(amount, payer_id, participants, share);
                break;
            case Percentage:
                percentage_split_.splitAmount(amount, payer_id, participants, share);
                break;
            default:
                throw invalid_argument("Invalid Split type!!\n");
        }
    }
};

#endif