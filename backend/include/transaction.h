#pragma once
#include <string>
using namespace std;

class Transaction {
private:
    double amount;
    int id;
    string desc;
    string categ;
    string type;
    string date;

public:
    Transaction(int id, double a, string d, string c, string t, string da);

    double getAmount() const;
    int getID() const;
    string getDescription() const;
    string getCategory() const;
    string getType() const;
    string getDate() const;
    static bool isValidDate(const string& date);

    void display() const;
    void update(double a, string d, string c, string t, string da);
};