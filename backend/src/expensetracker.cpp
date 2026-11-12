#include "expensetracker.h"
#include <iostream>
using namespace std;

void ExpenseTracker::addTransaction(double a, string d, string c, string t, string da) {
    transactions.push_back(Transaction(nextid, a, d, c, t, da));
    nextid++;
}

void ExpenseTracker::showAllTransactions() const {
    for (const auto& i : transactions) {
        i.display();
    }
}

bool ExpenseTracker::deleteTransaction(int id) {
    for(size_t i = 0; i < transactions.size(); i++) {
        if (transactions[i].getID() == id) {
            transactions.erase(transactions.begin() + i);
            return true;
        }
    }
    return false;
}

bool ExpenseTracker::editTransaction(int id, double a, string d, string c, string t, string da) {
    for (size_t i = 0; i < transactions.size(); i++) {
        if (transactions[i].getID() == id) {
            transactions[i].update(a, d, c, t, da);
            return true;
        }
    }
    return false;
}

double ExpenseTracker::getTotalIncome() const {
    double income = 0;

    for (const auto& i : transactions) {
        if (i.getType() == "income") {
            income += i.getAmount();
        }
    }

    return income;
}

double ExpenseTracker::getTotalExpenses() const {
    double expense = 0;

    for (const auto& i : transactions) {
        if (i.getType() == "expense") {
            expense += i.getAmount();
        }
    }

    return expense;
}

double ExpenseTracker::getBalance() const {
    return getTotalIncome() - getTotalExpenses();
}

vector<Transaction> ExpenseTracker::getTransactionsByDate(string startDate, string endDate) const {
    if (!Transaction::isValidDate(startDate) || !Transaction::isValidDate(endDate)) {
        throw invalid_argument("Invalid starting and ending dates.");
    }
    if (startDate > endDate) {
        throw invalid_argument("Invalid starting and ending dates.");
    }
    vector<Transaction> filtered;
    for (size_t i = 0; i < transactions.size(); i++) {
        string date = transactions[i].getDate();
        if (date >= startDate && date <= endDate) {
            filtered.push_back(transactions[i]);
        }
    }
    return filtered;
}

vector<Transaction> ExpenseTracker::getTransactionsByType(string type) const {
    if (type != "income" && type != "expense") {
        throw invalid_argument("Type must be income or expense.");
    }
    vector<Transaction> filtered;
    for (size_t i = 0; i < transactions.size(); i++) {
        if (transactions[i].getType() == type) {
            filtered.push_back(transactions[i]);
        }
    }
    return filtered;
}

vector<Transaction> ExpenseTracker::getTransactionsByCategory(string category) const {
    if (category.empty()) {
        throw invalid_argument("Category cannot be empty.");
    }
    vector<Transaction> filtered;
    for (size_t i = 0; i < transactions.size(); i++) {
        if (transactions[i].getCategory() == category) {
            filtered.push_back(transactions[i]);
        }
    }
    return filtered;
}

double ExpenseTracker::getMonthlyIncome(int year, int month) const {
    if (year < 1000 || year > 9999 || month > 12 || month < 1) {
        throw invalid_argument("Invalid year or month.");
    }
    double monthlyIncome = 0;
    string y = to_string(year);
    string m = to_string(month);
    string check = "";
    if (month < 10) {
        check = y + "-0" + m; 
    }
    else {
        check = y + '-' + m; 
    }
    for (size_t i = 0; i < transactions.size(); i++) {
        if (transactions[i].getDate().substr(0, 7) == check && transactions[i].getType() == "income") {
            monthlyIncome += transactions[i].getAmount();
        }
    }
    return monthlyIncome;
}

double ExpenseTracker::getMonthlyExpenses(int year, int month) const {
    if (year < 1000 || year > 9999 || month > 12 || month < 1) {
        throw invalid_argument("Invalid year or month.");
    }
    double monthlyExpense = 0;
    string y = to_string(year);
    string m = to_string(month);
    string check = "";
    if (month < 10) {
        check = y + "-0" + m; 
    }
    else {
        check = y + '-' + m; 
    }
    for (size_t i = 0; i < transactions.size(); i++) {
        if (transactions[i].getDate().substr(0, 7) == check && transactions[i].getType() == "expense") {
            monthlyExpense += transactions[i].getAmount();
        }
    }
    return monthlyExpense;
}

double ExpenseTracker::getMonthlyBalance(int year, int month) const {
    if (year < 1000 || year > 9999 || month > 12 || month < 1) {
        throw invalid_argument("Invalid year or month.");
    }
    return getMonthlyIncome(year, month) - getMonthlyExpenses(year, month);
}