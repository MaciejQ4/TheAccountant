// TheAccountant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Accountant.h"
#include "AuxillaryFunctions.h"
#include <iostream>

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    Accountant accountant("users", "incomes", "expenses");

    while (true) {

        if (accountant.isUserLogged() == false) {

        system("cls");
        cout << ">> ACCOUNTANT MAIN MENU <<" << endl << endl;
        cout << "1. Create new User"         << endl;
        cout << "2. Login"                   << endl;
        cout << "3. Show all Users"          << endl;
        cout << "9. Close The Accountant"    << endl;

        char choice = AuxillaryFunctions::readChar();
        switch (choice) {

        case '1': accountant.createUser();              break;
        case '2': accountant.loginUser();               break;
        case '3': accountant.showAllUsers();            break;
        case '9': exit(0);                              break;

        default: cout << "Wrong input. "; system("pause");
        }
        }
        //////////////////////////////////////////////////////
        else {

            system("cls");
            cout << ">> SUB MENU <<" << endl << endl;
            cout << "1. Date and time right now" << endl;
            cout << "2. Calculate elapsed time between two dates" << endl;
            cout << "3. Current months number of days" << endl;
            cout << "4. create income" << endl;
            cout << "5. show incomes" << endl;
            cout << "6. create expense" << endl;
            cout << "7. show expenses" << endl;
            cout << "8. show this months balance" << endl;

            char choice = AuxillaryFunctions::readChar();
            switch (choice) {

            case '1': accountant.showCurrentTime();         break;
            case '2': accountant.calculateTimeDifference(); break;
            case '3': accountant.howManyDays();             break;
            case '4': accountant.createIncome();            break;
            case '5': accountant.showIncomes();             break;
            case '6': accountant.createExpense();            break;
            case '7': accountant.showExpenses();             break;
            case '8': accountant.showBalance();             break;
          

            default: cout << "Wrong input. "; system("pause");
            }
        }
    
    
    
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
