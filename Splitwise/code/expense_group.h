#ifndef EXPENSE_GROUP_H
#define EXPENSE_GROUP_H

#include <iostream>
#include <random>
#include <unordered_map>
#include "utils.h"
#include "manager/manger_base.h"

using namespace std;

/**
 * @brief Represents a group where people can create to track transactions
 * related to a common theme.
 * Eg Flat mates can create a group flat-expenses to track the expenses related
 * to flat. Each flat resident can be part of that group.
 */
class ExpenseGroup {
private:
    //! name of the group
    string name_ = "";
    //! GroupId of Expense group
    string group_id_ = "";
    //! Any other string metadata/description for the expense
    string details_ = "";
    //! Tracks the people who are part of this group
    unordered_set<string> participants_;
public:
    ExpenseGroup(string name, int amount, vector<string>& participants,
        string details = "") {
        this->name_ = name;
        this->group_id_ = getUniqueId(5);

        participants_(participants.begin(), participants.end());
        
        // Set metadata if any
        if(details.size() > 0)
            this->details_ = details;
    }

    string getName() const { return name_; }

    string getGroupId() const { return group_id_; }

    string getDetails() const { return details_; }

    void addParticipant(string personId) {
        // Idempotent operation, if a person is already
        // present, no change is observed
        this->participant.emplace(personId);
    }
};

//! Sample hash function for above class: This is not a really good one
struct HashExpenseGroup {
    size_t operator()(const ExpenseGroup& expense_group) const {
        return hash<string>()(expense_group.getName())
            ^ hash<string>()(expense_group.getGroupId()) << 1;
    }
};

#endif