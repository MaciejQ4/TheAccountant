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

string AuxillaryFunctions::addDashToDate(int date) {

    string dateString = to_string(date);

    char dateArray[10];

    dateArray[0] = dateString[0];
    dateArray[1] = dateString[1];
    dateArray[2] = dateString[2];
    dateArray[3] = dateString[3];
    dateArray[4] = '-';
    dateArray[5] = dateString[4];
    dateArray[6] = dateString[5];
    dateArray[7] = '-';
    dateArray[8] = dateString[6];
    dateArray[9] = dateString[7];

    string dateStringModified = "";

    for (size_t i = 0; i < 10; i++)
        dateStringModified += dateArray[i];

    //string dateStringModified = dateString.substr(0, 4) + '-' + dateString.substr(4, 2) + '-' + dateString.substr(6, 2);
    return dateStringModified;
}

int AuxillaryFunctions::eraseDashFromDate(string date) {

    char dateArray[8];
    dateArray[0] = date[0];
    dateArray[1] = date[1];
    dateArray[2] = date[2];
    dateArray[3] = date[3];
    dateArray[4] = date[5];
    dateArray[5] = date[6];
    dateArray[6] = date[8];
    dateArray[7] = date[9];

    string dateStringConverted = "";

    for (size_t i = 0; i < 8; i++)
        dateStringConverted += dateArray[i];

    int dateInt = stoi(dateStringConverted);
    return dateInt;
}