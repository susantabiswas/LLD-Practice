#ifndef SPLITWISE_CPP
#define SPLITWISE_CPP

#include <iostream>
#include "split_technique/exact_split.h"
#include "manager.h"
#include "user.h"
#include "expense.h"
#include "expense_group.h"

using namespace std;

class Splitwise {
private:
    Manager<User> user_manager_;
    Manager<Expense> expense_manager_;
    Manager<ExpenseGroup> expense_group_manager_;

public:
    ////////////////////////////////// User related Operations ///////////////////////
    void registerUser(string name, string email,
        string phone_number) {
        User* user = new User(name, email, phone_number);
        try {
            this->user_manager_.addInstance(user->getUserId(), user);
        }
        catch(InstanceAlreadyExists) {
            cout << "User with same Id already exists!\n";
        }
    }

    void deregisterUser(string user_id) {
        try {
            this->user_manager_.removeInstance(user_id);
        }
        catch(NotFoundException e) {
            cout << e.what() ;
        }
    }

    ////////////////////////////////// Expense related Operations ///////////////////////
    void addExpense(string name, int amount, vector<string>& participants,
        string details = "", string group_id = "") {
        Expense* expense = new Expense(name, amount, participants, details, group_id);
        try {
            this->expense_manager_.addInstance(expense->getExpenseId(), expense);
        }
        catch(InstanceAlreadyExists) {
            cout << "Expense with same Id already exists!\n";
        }
    }

    void deleteExpense(string expense_id) {
        try {
            this->expense_manager_.removeInstance(expense_id);
        }
        catch(NotFoundException e) {
            cout << e.what() ;
        }
    }

    ////////////////////////////////// Expense Group related Operations ///////////////////////
    void addExpenseGroup(string name, vector<string>& participants,
        string details = "") {
        ExpenseGroup* expense_group = new ExpenseGroup(name, participants, details);
        try {
            this->expense_group_manager_.addInstance(
                expense_group->getGroupId(), expense_group);
        }
        catch(InstanceAlreadyExists) {
            cout << "Expense with same Id already exists!\n";
        }
    }

    void deleteExpenseGroup(string expense_group_id) {
        try {
            this->expense_group_manager_.removeInstance(expense_group_id);
        }
        catch(NotFoundException e) {
            cout << e.what() ;
        }
    }
};

int main() {

}

#endif