#include "AuxillaryFunctions.h"

string AuxillaryFunctions::readLine() {

    //cin.ignore(); //sometimes usefull sometimes not
    string input = "";
    getline(cin, input);
    return input;
}

char AuxillaryFunctions::readChar() {

    char character = { 0 };

    while (true)
    {
        string input = AuxillaryFunctions::readLine();

        if (input.length() == 1) {

            character = input[0];
            return character;
        }
        else {
            character = 'x';
            return character;
        }
    }
}