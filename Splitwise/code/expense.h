#ifndef EXPENSE_H
#define EXPENSE_H

#include <iostream>
#include <random>
#include <unordered_map>
#include "borrowing.h"
#include "person.h"

using namespace std;

/**
 * @brief Represents an instance of Expenditure in terms of money.
 * 
 */
class Expense {
private:
    string name_ = "";
    // GroupId of Expense group if any
    string expense_group_id_ = "";
    // Any other string metadata/description for the expense
    string details_ = "";
    // Total amount for the expense
    int amount_ = 0;
    // <PersonId>: People part of this expense
    unordered_set<string> participants_;
public:
    
    Expense(string name, int amount, vector<string>& participants,
        string details = "", string group_id = "") {
        this->name_ = name;
        
        participants_(participants.begin(), participants.end());

        // Set Expense Group Id and metadata if any
        if(details.size() > 0)
            this->details_ = details;
        if(group_id.size() > 0)
            this->expense_group_id_ = group_id;
    }


    string getName() const { return name_; }

    string getGroupId() const { return expense_group_id_; }

    string getDetails() const { return details_; }

    int getAmount() const { return amount_; }

    vector<string> getParticipants() {
        return vector<string>(this->participants_.begin(),
            this->participants_.end());
    }
    
    void addParticipant(string personId) {
        // Idempotent operation
        this->participants_.emplace([personId]);
    }
};

//! Sample hash function for above class: This is not a really good one
struct HashExpense {
    size_t operator()(const Expense& expense) const {
        return hash<string>()(expense.getName())
            ^ hash<string>()(expense.getGroupId()) << 1
            ^ hash<int>()(expense.getAmount()) << 1;
    }
};


#endif