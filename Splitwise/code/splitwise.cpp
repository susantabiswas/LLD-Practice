#ifndef SPLITWISE_CPP
#define SPLITWISE_CPP

#include <iostream>
#include "split_techniques/split_controller.h"
#include "resource_manager.h"
#include "user.h"
#include "expense.h"
#include "expense_group.h"

using namespace std;

class Splitwise {
private:
    ResourceManager<User> user_manager_;
    ResourceManager<Expense> expense_manager_;
    ResourceManager<ExpenseGroup> expense_group_manager_;

    SplitController split_controller_;

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

    
    void showOwedUsers(string user_id) {
        if(!isPresent(user_manager_, user_id))
            throw NotFoundException();

        // Get the instance of current user
        User* user = this->user_manager_.getInstance(user_id);
        // get the user ids of people who are owed money
        unordered_map<string, double> owed_ids = user->getOwedUsers();

        cout << "User: " << user->getName() << " (" << user->getUserId() << ") owes money to the following people:\n\n";
        // print the owed people's name and amount owed
        for(auto [owed_user_id, amount] : owed_ids) {
            auto owed_user = this->user_manager_.getInstance(owed_user_id);
            cout << "Name: " << owed_user->getName() << " Amount: " << amount << endl;
        }
    }
    ////////////////////////////////// Expense related Operations ///////////////////////
    void addExpense(string name, int amount, string payer_id, vector<string>& participants,
        string details = "", string group_id = "") {

        // check if expense group exists
        if(!group_id.empty() && !this->expense_group_manager_.isPresent(group_id)) 
            throw NotFoundException();

        // create expense
        Expense* expense = new Expense(name, amount, payer_id,participants, details, group_id);

        // add the expense to expense resource_manager
        try {
            this->expense_manager_.addInstance(expense->getExpenseId(), expense);
        }
        catch(InstanceAlreadyExists) {
            cout << "Expense with same Id already exists!\n";
        }
        // add the expense to expense group
        if(!group_id.empty())
            this->expense_group_manager_
                .getInstance(group_id)->addExpense(expense->getExpenseId());
    }

    void deleteExpense(string expense_id) {
        // remove the expense from a expense group if any
        string expense_group_id = this->expense_manager_
            .getInstance(expense_id)->getGroupId();

        try {        
            if(!expense_group_id.empty())
                this->expense_group_manager_.removeInstance(expense_group_id);
        }
        catch(NotFoundException) {
            cout << "Group Id not found!\n";
        }

        // delete the expense
        try {
            this->expense_manager_.removeInstance(expense_id);
        }
        catch(NotFoundException e) {
            cout << "Expense Id not found!\n";
        }
    }

    ////////////////////////////////// Expense Group related Operations ///////////////////////
    void addExpenseGroup(string name, vector<string>& participants, string details = "") {
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

    
    void showExpenseGroups() {
        auto groups = expense_group_manager_.getAllInstances();
        for(auto [group_id, group] : groups) 
            describeExpenseGroup(group_id);
    }

    void describeExpenseGroup(string group_id) {
        if(!isPresent(expense_group_manager_, group_id))
            throw NotFoundException();

        auto group = expense_group_manager_.getInstance(group_id);
        cout << "########### Expense Group details ##############\n";
        cout << "Group Name : " << group->getName() << endl;
        cout << "Group Id : " << group->getGroupId() << endl;

        cout << "       Expenses     \n";
    }

    ////////////////////////////////////// Expense related operations /////////////////////
    void splitAmount(SplitType split_type, double amount, string payer_id, 
        vector<User*>& participants, vector<double> share = {}) {
        try {
            split_controller_.splitAmount(split_type, amount, payer_id, participants, share);
        }
        catch(ShareNotEqualToTotal e) {
            cout << e.what();
        }
        catch(invalid_argument e) {
            cout << e.what();
        }
    }

    void showUserExpenses(string user_id) {
        // get the user
        auto user = this->user_manager_.getInstance(user_id);
        // get the expense ids of all the expenses for the current user
        unordered_set<string> expense_ids = user->getExpenses();

        cout << "User: " << user->getName() << "(" << user->getUserId() << ") 's expenses\n";
        for(auto expense_id: expense_ids) {
            describeExpense(expense_id);
        }
    }

    void describeExpense(string expense_id) {
        if(!isPresent(expense_manager_, expense_id))
            throw NotFoundException();

        auto expense = expense_manager_.getInstance(expense_id);
            cout << "Expense details:\n";
            cout << "Expense Name: " << expense->getName() << endl;
            cout << "Amount: " << expense->getAmount() << endl;
            cout << "Participants: ";

            for(auto user_id : expense->getParticipants())
                cout << user_manager_.getInstance(user_id)->getName() << ", ";
        cout << endl;
    }

    void showAllUsersExpenses() {
        auto users = user_manager_.getAllInstances();
        for(auto [user_id, user] : users) 
            showUserExpenses(user_id);
    }


    template <typename T>
    bool isPresent(T& resource_manager, string id) {
        return resource_manager.isPresent(id);
    }
};

int main() {

}

#endif