#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"

using namespace std;

/**
 * @brief Represents a user. Has basic details
 * associated with a user like name, email etc.
 * 
 */
class User {
private:
    string name_;
    string user_id_;
    string email_;
    string phone_number_;

    //! People who are owed money by this user
    // <userId, amount owed>
    unordered_map<string, double> owed_;
    
    //! Tracks all the expense transactions involving this user
    // <expenseId>
    unordered_set<string> expenses_;
    
    // Tracks all the expense groups this user is part of
    unordered_set<string> expense_groups_;

public:
    User(string name, string email, string phone_number)
        : name_(name), email_(email), phone_number_(phone_number) {
        this->user_id_ = getUniqueId(5);
    }
    string getName() const { return name_; }

    string getUserId() const { return user_id_; }

    string getEmail() const { return email_; }

    string getPhoneNumber() const { return phone_number_; }

    void addUserOwed(string user_id, double amt) {
        this->owed_[user_id] += amt;
    }

    void addExpense(string expense_id) {
        this->expenses_.emplace(expense_id);
    }

    void addExpenseGroup(string expense_group_id) {
        this->expense_groups_.emplace(expense_group_id);
    }

    unordered_set<string> getExpenses() const {
        return this->expenses_;
    }

    unordered_set<string> getExpenseGroups() const {
        return this->expense_groups_;
    }

    unordered_map<string, double> getOwedUsers() const {
        return this->owed_;
    }
};

//! Sample hash function for above class: This is not a really good one
struct HashUser {
    size_t operator()(const User& user) const {
        return hash<string>()(user.getName())
            ^ hash<string>()(user.getUserId()) << 1
            ^ hash<string>()(user.getEmail()) << 1
            ^ hash<string>()(user.getPhoneNumber());
    }
};

#endif