#include <iostream>
#include <cassert>
#include <stdexcept>
#include "expensetracker.h"

using namespace std;

int main() {
    ExpenseTracker tracker;

    cout << "===== EXPENSE TRACKER TESTS =====\n\n";

    // TEST 1: Adding transactions
    tracker.addTransaction(5000, "Allowance", "Personal", "income", "2026-11-02");
    tracker.addTransaction(350, "Lunch", "Food", "expense", "2026-11-05");
    tracker.addTransaction(200, "Coffee", "Food", "expense", "2026-11-12");
    tracker.addTransaction(2000, "Freelancing", "Work", "income", "2026-11-20");
    tracker.addTransaction(400, "Shopping", "Shopping", "expense", "2026-10-28");

    assert(tracker.getTotalIncome() == 7000);
    assert(tracker.getTotalExpenses() == 950);
    assert(tracker.getBalance() == 6050);

    cout << "[PASS] Adding transactions and calculating totals\n";

    // TEST 2: Display transactions
    cout << "\nAll transactions:\n";
    tracker.showAllTransactions();

    // TEST 3: Monthly summaries
    assert(tracker.getMonthlyIncome(2026, 11) == 7000);
    assert(tracker.getMonthlyExpenses(2026, 11) == 550);
    assert(tracker.getMonthlyBalance(2026, 11) == 6450);

    assert(tracker.getMonthlyExpenses(2026, 10) == 400);
    assert(tracker.getMonthlyIncome(2026, 12) == 0);

    cout << "\n[PASS] Monthly summaries\n";

    // TEST 4: Date filtering
    vector<Transaction> november =
        tracker.getTransactionsByDate("2026-11-01", "2026-11-30");

    assert(november.size() == 4);
    cout << "[PASS] Date filtering\n";

    // TEST 5: Category filtering
    vector<Transaction> food =
        tracker.getTransactionsByCategory("Food");

    assert(food.size() == 2);
    cout << "[PASS] Category filtering\n";

    // TEST 6: Type filtering
    vector<Transaction> expenses =
        tracker.getTransactionsByType("expense");

    assert(expenses.size() == 3);
    cout << "[PASS] Type filtering\n";

    // TEST 7: Editing transaction
    bool edited = tracker.editTransaction(
        2, 500, "Dinner", "Food", "expense", "2026-11-05"
    );

    assert(edited == true);
    assert(tracker.getTotalExpenses() == 1100);
    assert(tracker.getMonthlyExpenses(2026, 11) == 700);

    cout << "[PASS] Editing transactions\n";

    // TEST 8: Deleting transaction
    bool deleted = tracker.deleteTransaction(3);

    assert(deleted == true);
    assert(tracker.getTotalExpenses() == 900);
    assert(tracker.getBalance() == 6100);

    cout << "[PASS] Deleting transactions\n";

    // TEST 9: Nonexistent IDs
    assert(tracker.deleteTransaction(999) == false);

    assert(tracker.editTransaction(
        999, 100, "Test", "Food", "expense", "2026-11-12"
    ) == false);

    cout << "[PASS] Nonexistent transaction IDs\n";

    // TEST 10: Invalid date
    bool exceptionCaught = false;

    try {
        tracker.addTransaction(
            100, "Invalid", "Food", "expense", "2026-02-30"
        );
    }
    catch (const invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);
    cout << "[PASS] Invalid date validation\n";

    // TEST 11: Invalid amount
    exceptionCaught = false;

    try {
        tracker.addTransaction(
            -100, "Invalid", "Food", "expense", "2026-11-12"
        );
    }
    catch (const invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);
    cout << "[PASS] Invalid amount validation\n";

    // TEST 12: Invalid transaction type
    exceptionCaught = false;

    try {
        tracker.addTransaction(
            100, "Test", "Food", "shopping", "2026-11-12"
        );
    }
    catch (const invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);
    cout << "[PASS] Invalid type validation\n";

    // TEST 13: Invalid date range
    exceptionCaught = false;

    try {
        tracker.getTransactionsByDate(
            "2026-12-01", "2026-11-01"
        );
    }
    catch (const invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);
    cout << "[PASS] Invalid date range validation\n";

    // TEST 14: ID uniqueness after deletion
    tracker.addTransaction(
        100, "Snacks", "Food", "expense", "2026-11-25"
    );

    // IDs 1-5 were assigned originally.
    // After deleting ID 3, the next ID should still be 6.
    vector<Transaction> snacks =
        tracker.getTransactionsByCategory("Food");

    bool foundID6 = false;

    for (const auto& t : snacks) {
        if (t.getID() == 6) {
            foundID6 = true;
        }
    }

    assert(foundID6);
    cout << "[PASS] Unique IDs after deletion\n";

    cout << "\n===== ALL TESTS PASSED! =====\n";

    return 0;
}
