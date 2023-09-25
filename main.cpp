// TheAccountant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Accountant.h"
#include "AuxillaryFunctions.h"
#include <iostream>

using namespace std;

int main()
{
    Accountant accountant("users.xml", "incomes.xml", "expenses.xml");

    while (true) {

        if (accountant.isUserLogged() == false) {

        system("cls");
        cout << ">>> ACCOUNTANT - MAIN MENU <<<"         << endl << endl << endl;
        cout << "1. Create new User"                     << endl;
        cout << "2. Login"                               << endl << endl;
        //cout << "3. Show all Users"                      << endl;
        cout << "------------------------------"         << endl << endl;
        cout << "9. Close application"                   << endl;

        char choice = AuxillaryFunctions::readChar();
        switch (choice) {

        case '1': accountant.createUser();              break;
        case '2': accountant.loginUser();               break;
        //case '3': accountant.showAllUsers();            break;
        case '9': exit(0);                              break;

        default: cout << "Wrong input. "; system("pause");
        }
        }
        ////////////////////////////////////////////////////////////////////////
        else {

            system("cls");
            cout << ">>> USER MENU <<<"                                 << endl << endl << endl;
            cout << "1. Add income"                                     << endl;
            cout << "2. Add expense"                                    << endl << endl;
            cout << "-----------------------------------------"         << endl << endl;
            cout << "3. Show this months balance"                       << endl;
            cout << "4. Show previous months balance"                   << endl;
            cout << "5. Show balance for requested time period"         << endl << endl;
            cout << "-----------------------------------------"         << endl << endl;
            cout << "6. Change password"                                << endl;
            cout << "7. Logout"                                         << endl;

            char choice = AuxillaryFunctions::readChar();
            switch (choice) {

            case '1': accountant.createTransaction(INCOME);       break;
            case '2': accountant.createTransaction(EXPENSE);      break;
            case '3': accountant.showBalance(THIS_MONTH);         break;
            case '4': accountant.showBalance(PREVIOUS_MONTH);     break;
            case '5': accountant.showBalance(CUSTOM_PERIOD);      break;
            case '6': accountant.changePassword();                break;
            case '7': accountant.logOut();                        break;

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
