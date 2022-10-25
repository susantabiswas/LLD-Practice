#ifndef MAIN_CPP
#define MAIN_CPP

#include "splitwise.h"
using namespace std;

int main() {
    Splitwise splitwise;

    ///////////////// create users
    User* u1 = splitwise.registerUser("Ram", "ram@gmail.com", "23123");
    User* u2 = splitwise.registerUser("Shyam", "shyam@outlook.com", "43123");
    User* u3 = splitwise.registerUser("Ganshyam", "ganshyam@hotmail.com", "63123");
    User* u4 = splitwise.registerUser("Arjun", "arjun@gmail.com", "13123"); 

    auto u1_id = u1->getUserId();
    auto u2_id = u2->getUserId();
    auto u3_id = u3->getUserId();
    auto u4_id = u4->getUserId();

    /////////////////// Create expense groups
    ExpenseGroup* g1 = splitwise.addExpenseGroup("Flat mates", vector<string>{u1_id, u2_id, u3_id, u4_id},
                                        "Expenses for flatmates");
    ExpenseGroup* g2 = splitwise.addExpenseGroup("Outing", {u1_id, u2_id}, "Expenses for trip");


    string g1_id = g1->getGroupId();
    auto g2_id = g2->getGroupId();

    ///////////////// Expenses under Flat mates group

    // Split type should be taken Equal by default
    // Ram: 33.34, Shyam: 33.33, Ganshyam: 33.33, Arjun: 0
    Expense* lunch = splitwise.addExpense("lunch", 100, u1, {u1_id, u2_id, u3_id},
            "Lunch Pizza", g1_id, Equal);
    splitwise.showAllOwedUsers();

    // Split type is Exact
    // Ram: 45 + 33.34, Shyam: 55 + 33.33, Ganshyam: 900 + 33.33, Arjun: 0  
    Expense* dinner = splitwise.addExpense("dinner", 1000, u1, vector<string>{u1_id, u2_id, u3_id, u4_id},
            "dinner Pizza", g1_id, Exact, {45, 55, 900, 0});
    splitwise.showAllOwedUsers();

    // Split type is Percentage 
    // Ram: 120, Shyam: 140, Ganshyam: 0, Arjun: 140  
    Expense* electricity = splitwise.addExpense("electricity", 400, u3, vector<string>{u1_id, u2_id, u3_id, u4_id},
            "Lunch Pizza", g1_id, Percentage, {0.3, 0.35, 0, 0.35});
    splitwise.showAllOwedUsers();


    // Expenses under Outing group
    // Split type is Percentage, but the % sum != 100. Invalid data, should throw exception 
    try {
        Expense* lunch_pizza = splitwise.addExpense("lunch", 400, u3, vector<string>{u1_id, u3_id, u4_id},
                "Lunch Pizza", g2_id, Percentage, {1.0, 0.5, 0.5});
    }
    catch(exception e) {
        cout << "[Exception]: " << e.what() << endl;
    }
    
    try {
        // Split type is Exact, but the sum of individual shares != total. Invalid data, should throw exception        
        Expense* flight = splitwise.addExpense("lunch", 14000, u4, vector<string>{u1_id, u2_id, u3_id, u4_id},
                "Flight Tickets", g2_id, Exact, {7000, 100, 100, 100});
    }
    catch(ShareNotEqualToTotal e) {
        cout << "[Exception]: " << e.what() << endl;
    }

    // Individual expenses
    // Ram: 800, Shyam: 0, Ganshyam: 0, Arjun: 600  
    splitwise.addExpense("airport cab", 1400, u4, vector<string>{u1_id, u4_id},
            "", "", Exact, {800, 600});
    // splitwise.showAllUsersExpenses();
    splitwise.showAllOwedUsers();

    // Ram: 0, Shyam: 30.30, Ganshyam: 0, Arjun: 269.7  
    splitwise.addExpense("Auto fare", 300, u2, vector<string>{u2_id, u4_id},
            "", "", Percentage, {.101, .899});
    // splitwise.showAllUsersExpenses();
    splitwise.showAllOwedUsers();

    // //////////// Show expenses for user1
    splitwise.showUserExpenses(u1_id);

    // //////////// Show all the people user 1 owe money
    splitwise.showOwedUsers(u1_id);

    // ////////////// Show expenses for all users
    splitwise.showAllUsersExpenses();

    // /////////// Show all expense groups
    splitwise.showAllExpenseGroups();

    splitwise.describeExpenseGroup(g1_id);
}

#endif