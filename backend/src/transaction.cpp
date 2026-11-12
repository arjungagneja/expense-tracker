#include "transaction.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Transaction::Transaction(int id, double a, string d, string c, string t, string da)
    : id(id), amount(a), desc(d), categ(c), type(t), date(da) {
    if (amount <= 0) {
        throw invalid_argument("Amount must be greater than zero.");
    }

    if (type != "income" && type != "expense") {
        throw invalid_argument("Type must be income or expense.");
    }

    if (desc.empty() || categ.empty()) {
        throw invalid_argument("Description and category cannot be empty.");
    }

    if (!isValidDate(da)) {
        throw invalid_argument("Invalid date.");
    }
}

void Transaction::update(double a, string d, string c, string t, string da) {
    if (a <= 0) {
        throw invalid_argument("Amount must be greater than zero.");
    }
    if (t != "income" && t != "expense") {
        throw invalid_argument("Type must be income or expense.");
    }
    if (d.empty() || c.empty()) {
        throw invalid_argument("Description and category cannot be empty.");
    }
    if (!isValidDate(da)) {
        throw invalid_argument("Invalid date.");
    }

    amount = a;
    desc = d;
    categ = c;
    type = t;
    date = da;
}

string Transaction::getDate() const {
    return date;
}

int Transaction::getID() const {
    return id;
}

double Transaction::getAmount() const {
    return amount;
}

string Transaction::getDescription() const {
    return desc;
}

string Transaction::getCategory() const {
    return categ;
}

string Transaction::getType() const {
    return type;
}

void Transaction::display() const {
    cout << id << " | " << type << " | " << categ << " | "
              << amount << " | " << desc << " | " << date << endl;
}

bool Transaction::isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    for (size_t i = 0; i < date.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(date[i]))) {
            if (i == 4 || i == 7) {
                continue;
            }
            return false;
        }
    }
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (year < 1) {
        return false;
    }
    if (month > 12 || month < 1) {
        return false;
    }
    if (day > 31 || day < 1) {
        return false;
    }
    if (month == 2) {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
            if (day > 29) {
                return false;
            }
        }
        else {
            if (day > 28) {
                return false;
            }
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false;
        }
    }
    return true;
}