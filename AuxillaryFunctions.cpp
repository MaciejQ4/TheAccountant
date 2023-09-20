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

string AuxillaryFunctions::addDashesToDate(int date) {

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

int AuxillaryFunctions::eraseDashesFromDate(string date) {

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

bool AuxillaryFunctions::isLeapYear(int year) {

    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int AuxillaryFunctions::getTodaysDate()
{
	std::time_t currentTime = time(nullptr);
	struct tm timeInfo;
	char timeBuffer[26];

	if (localtime_s(&timeInfo, &currentTime) == 0 && asctime_s(timeBuffer, sizeof(timeBuffer), &timeInfo) == 0) {
		//cout << "Current time: " << timeBuffer << endl;
	}
	else {
		cout << "Error getting todays date from PC.";
		system("pause");
		return 0;
	}

	char dateTodayArray[8];
	if (timeInfo.tm_mday < 10) {
		dateTodayArray[6] = 0 + '0';
		dateTodayArray[7] = timeInfo.tm_mday + '0';
	}
	else {
		dateTodayArray[6] = (timeInfo.tm_mday / 10) + '0';
		dateTodayArray[7] = (timeInfo.tm_mday % 10) + '0';
	}
	timeInfo.tm_mon += 1;
	if (timeInfo.tm_mon < 10) {
		dateTodayArray[4] = 0 + '0';
		dateTodayArray[5] = timeInfo.tm_mon + '0';
	}
	else {
		dateTodayArray[4] = (timeInfo.tm_mon / 10) + '0';
		dateTodayArray[5] = (timeInfo.tm_mon % 10) + '0';
	}
	timeInfo.tm_year += 1900;
	dateTodayArray[0] = (timeInfo.tm_year / 1000) + '0';
	dateTodayArray[1] = ((timeInfo.tm_year / 100) % 10) + '0';
	dateTodayArray[2] = ((timeInfo.tm_year / 10) % 10) + '0';
	dateTodayArray[3] = (timeInfo.tm_year % 10) + '0';

	string dateString = "";
	for (int i = 0; i < 8; i++)
		dateString += dateTodayArray[i];

	//cout << dateString;
	int dateToday = stoi(dateString);
	return dateToday;
}

int AuxillaryFunctions::elapsedDaysThisMonth()
{
	time_t currentTime = time(nullptr);
	struct tm timeInfo;
	char timeBuffer[26];

	if (localtime_s(&timeInfo, &currentTime) == 0 && asctime_s(timeBuffer, sizeof(timeBuffer), &timeInfo) == 0) {
		return timeInfo.tm_mday;
	}
	else {
		cout << "Error getting time from PC. ";
		system("pause");
		return 0;
	}
}

bool AuxillaryFunctions::checkDateFormat(string userInputDate)
{
	if (userInputDate.size() != 10) {							// check input isnt too long to be ok
		cout << "Wrong input format. " << endl;
		return false;
	}

	if (userInputDate[4] != '-' || userInputDate[7] != '-') {	// check if seperated properly by '-' symbols in the right place
		cout << "Wrong input format. " << endl;
		return false;
	}

	char dateArray[8];
	dateArray[0] = userInputDate[0];
	dateArray[1] = userInputDate[1];
	dateArray[2] = userInputDate[2];
	dateArray[3] = userInputDate[3];
	dateArray[4] = userInputDate[5];
	dateArray[5] = userInputDate[6];
	dateArray[6] = userInputDate[8];
	dateArray[7] = userInputDate[9];

	for (size_t i = 0; i < 8; i++) {
		if (!(isdigit(dateArray[i]))) {							// check if input is made of digits only
			cout << "Wrong input format. " << endl;
			return false;
		}
	}

	string yearString = "";										// check year part of inputed string ([XXXX]-MM-DD)
	for (size_t i = 0; i < 4; i++)
		yearString += dateArray[i];

	int year = stoi(yearString);

	bool leapYear = AuxillaryFunctions::isLeapYear(year);

	if (year < 2000) {
		cout << "Cannot enter year less then 2000. " << endl;
		return false;
	}

	string monthString = "";									// check month part of inputed string (YYYY-[XX]-DD)
	monthString += dateArray[4];
	monthString += dateArray[5];
	int month = stoi(monthString);
	if (month > 12) {
		cout << "Invalid month. " << endl;
		return false;
	}

	string dayString = "";										// check day part of inputed string (YYYY-MM-[XX])
	dayString += dateArray[6];
	dayString += dateArray[7];
	int day = stoi(dayString);

	if (day > 31 || day == 0) {
		cout << "Invalid day. a Month cannot have more than 31 or less than 1 days. " << endl;
		return false;
	}

	if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
		cout << "Invalid day. Inputed month can not have more than 30 days. " << endl;
		return false;
	}

	if (day > 29 && month == 2 && leapYear) {
		cout << "Invalid day. February cannot have more than 29 days in inputed(leap) year. " << endl;
		return false;
	}

	if (day > 28 && month == 2 && !leapYear) {
		cout << "Invalid day. February cannot have more than 28 days in inputed year. " << endl;
		return false;
	}

	string dateString = yearString + monthString + dayString;
	int date = stoi(dateString);
	if (date > getTodaysDate()) {						   // check if inputed date isnt a future date
		cout << "Can't input future date. " << endl;
		return false;
	}
	return true;
}

bool AuxillaryFunctions::checkAmountFormat(string inputAmount)
{
	for (size_t i = 0; i < inputAmount.size(); i++) {		  // check string for forbidden characters
		if (!(isdigit(inputAmount[i])) && inputAmount[i] != ',' && inputAmount[i] != '.') {
			cout << "Wrong input format. ";
			system("pause");
			return false;
		}
	}

	for (size_t i = 0; i < inputAmount.size(); i++) {		  // change all commas to dots
		if (inputAmount[i] == ',') inputAmount[i] = '.';
	}

	int dotCounter = 0;
	for (size_t i = 0; i < inputAmount.size(); i++) {		  // check string for too many dots
		if (inputAmount[i] == '.') dotCounter++;
	}

	if (dotCounter >= 2) {
		cout << "Wrong input format. " << endl;
		system("pause");
		return false;
	}

	int dotPlace = 0;
	for (size_t i = 0; i < inputAmount.size(); i++) {
		if (inputAmount[i] == '.') dotPlace = i;
	}

	for (size_t i = 0; i < inputAmount.size(); i++) {
		char ch = inputAmount[i];
		if (i == dotPlace && ch == '0') {
			cout << "Wrong input format. Leading zeros not allowed. " << endl;
			system("pause");
			return false;
		}
	}

	if ((inputAmount.size() - dotPlace > 3) && dotPlace != 0) {
		cout << "Wrong input format. More than two decimal places not allowed. ";
		system("pause");
		return false;
	}
	return true;
}
