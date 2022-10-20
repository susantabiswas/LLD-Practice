#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"

using namespace std;

/**
 * @brief Represents a person. Has basic details
 * associated with a person like name, email etc.
 * 
 */
class Person {
private:
    string name_;
    string user_id_;
    string email_;
    string phone_number_;

    //! People who are owed money by this person
    // <personId, amount owed>
    unordered_map<string, int> owed_;
    
    //! Tracks all the expense transactions involving this person
    // <expenseId>
    unordered_set<string> expenses_;
    
    // Tracks all the expense groups this person is part of
    unordered_set<string> expense_groups_;

public:
    string getName() const { return name_; }

    string getUserId() const { return user_id_; }

    string getEmail() const { return email_; }

    string getPhoneNumber() const { return phone_number_; }
};

//! Sample hash function for above class: This is not a really good one
struct HashPerson {
    size_t operator()(const Person& person) const {
        return hash<string>()(person.getName())
            ^ hash<string>()(person.getUserId()) << 1
            ^ hash<string>()(person.getEmail()) << 1
            ^ hash<string>()(person.getPhoneNumber());
    }
};

#endif