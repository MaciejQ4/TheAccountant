#include "OperationManager.h"
#include "AuxillaryFunctions.h"

void OperationManager::addTransaction()
{
    system("cls");
    Expense expense = gatherExpenseInfo();
    expenses.push_back(expense);
    expenseXML.appendTransactionToXML(expense);
    cout << "User added succesfully. ";  system("pause");
}

Expense OperationManager::gatherExpenseInfo() {

    Expense expense;
    expense.setTransactionID(expenseXML.getIDofLastTransaction() + 1);
    expense.setUserID(LOGGED_ID);
    expense.setDate(LOGGED_ID);

    cout << "Enter item: " << endl;
    string itemInput = AuxillaryFunctions::readLine();
    expense.setItem(itemInput);

    cout << "Enter amount: " << endl;
    int amountInput = stoi(AuxillaryFunctions::readLine());
    expense.setAmount(amountInput);

    return expense;
}

void OperationManager::showTransactions() {

    system("cls");
    if (expenses.empty()) { cout << "No expences in your account. "; system("pause"); }

    else {
        cout << "Expenses in your account:" << endl << endl;
        for (Expense expense : expenses) {
            cout << "ID: " << expense.getTransactionID() << endl;
            cout << "User ID: " << expense.getUserID() << endl;
            cout << "Date: " << expense.getDate() << endl;
            cout << "Item: " << expense.getItem() << endl;
            cout << "Amount: " << expense.getAmount() << endl << endl;
        }
        cout << endl; system("pause");
    }
}