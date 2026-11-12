#pragma once
#include <vector>
#include "transaction.h"
using namespace std;

class ExpenseTracker {
private:
    vector<Transaction> transactions;
    int nextid = 1;

public:
    void addTransaction(double a, string d, string c, string t, string da);
    void showAllTransactions() const;
    bool deleteTransaction(int id);
    bool editTransaction(int id, double a, string d, string c, string t, string da);
    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getBalance() const;
    double getMonthlyIncome(int year, int month) const;
    double getMonthlyExpenses(int year, int month) const;
    double getMonthlyBalance(int year, int month) const;
    vector<Transaction> getTransactionsByDate(string startDate, string endDate) const;
    vector<Transaction> getTransactionsByType(string type) const;
    vector<Transaction> getTransactionsByCategory(string category) const;
};