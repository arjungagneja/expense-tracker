#include <iostream>
#include "httplib.h"
#include "expensetracker.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

int main() {

    // Create tracker and add sample transactions
    ExpenseTracker tracker;

    tracker.addTransaction(Transaction(15000, "Freelance work", "Freelance", "income"));
    tracker.addTransaction(Transaction(5000, "Scholarship", "Education", "income"));

    tracker.addTransaction(Transaction(2000, "Groceries", "Food", "expense"));
    tracker.addTransaction(Transaction(1500, "Bus", "Travel", "expense"));
    tracker.addTransaction(Transaction(3000, "Clothes", "Shopping", "expense"));

    // Create HTTP server
    httplib::Server server;

    // Root endpoint
    server.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content(
            "Personal Finance Manager API is running!",
            "text/plain"
        );
    });

    // Health check endpoint
    server.Get("/api/health", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content(
            R"({"status":"ok"})",
            "application/json"
        );
    });

    // Financial summary endpoint
    server.Get("/api/summary", [&tracker](const httplib::Request& req, httplib::Response& res) {

        json summary = {
            {"totalIncome", tracker.getTotalIncome()},
            {"totalExpenses", tracker.getTotalExpenses()},
            {"balance", tracker.getBalance()}
        };

        res.set_content(summary.dump(4), "application/json");
    });

    cout << "Server running at http://localhost:8080" << endl;

    server.listen("localhost", 8080);

    return 0;
}