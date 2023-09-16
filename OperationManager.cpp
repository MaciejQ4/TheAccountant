#include "OperationManager.h"
#include "AuxillaryFunctions.h"

void OperationManager::showCurrentTime() {

	std::time_t currentTime = std::time(nullptr);
	struct tm timeInfo;
	char timeBuffer[26];

	if (localtime_s(&timeInfo, &currentTime) == 0 && asctime_s(timeBuffer, sizeof(timeBuffer), &timeInfo) == 0) {
		std::cout << "Current time: " << timeBuffer;
	}
	else {
		std::cout << "Error getting current time.";
	}
	cout << timeInfo.tm_mon;
	int a = timeInfo.tm_hour;
	cout << a;
	system("pause");
}

void OperationManager::calculateTimeDifference() {
	std::tm start{}, end{};

	cout << "Enter start date (YYYY-MM-DD): ";
	cin >> std::get_time(&start, "%Y-%m-%d");

	if (cin.fail()) {
		cout << "Invalid start date format. ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("pause");
		return;
	}


	cout << "Enter end date (YYYY-MM-DD): ";
	cin >> std::get_time(&end, "%Y-%m-%d");

	if (cin.fail()) {
		cout << "Invalid end date format. ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("pause");
		return;
	}

	std::time_t startTimestamp = std::mktime(&start);
	std::time_t endTimestamp = std::mktime(&end);

	std::chrono::duration<long long, std::ratio<24 * 60 * 60>> differenceDays =
		std::chrono::duration_cast<std::chrono::duration<long long, std::ratio<24 * 60 * 60>>>(std::chrono::seconds(endTimestamp - startTimestamp));

	long long days = differenceDays.count();

	cout << days << endl;
	system("pause");

	return;
}

bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int OperationManager::elapsedDaysThisMonth() {

	std::time_t currentTime = std::time(nullptr);
	struct tm timeInfo;
	char timeBuffer[26];

	if (localtime_s(&timeInfo, &currentTime) == 0 && asctime_s(timeBuffer, sizeof(timeBuffer), &timeInfo) == 0) {
		return timeInfo.tm_mday;
	}
	else {
		std::cout << "Error getting current time." ;
		system("pause");
		return 0;
	}
}

void OperationManager::addIncome()
{
    system("cls");
    Income income = gatherIncomeInfo();
    incomes.push_back(income);
    incomeXML.appendTransactionToXML(income);
}

void OperationManager::addExpense()
{
    system("cls");
    Expense expense = gatherExpenseInfo();
    expenses.push_back(expense);
    expenseXML.appendTransactionToXML(expense);
    cout << "Expense added succesfully. ";
	system("pause");
}

Income OperationManager::gatherIncomeInfo() {

    Income income;

    income.setTransactionID(incomeXML.getIDofLastIncome() + 1);
    income.setUserID(LOGGED_ID);

	system("cls");
	string itemInput = "";
	cout << "Enter item: " << endl;
	itemInput = AuxillaryFunctions::readLine();
	income.setItem(itemInput);

	string inputAmount = "";
	do {
		cout << "Enter amount: " << endl;
		inputAmount = AuxillaryFunctions::readLine();
		
	} while (!(checkAmountFormat(inputAmount)));
	
	
	for (size_t i = 0; i < inputAmount.size(); i++) {      // change comma to dot
		if (inputAmount[i] == ',') inputAmount[i] = '.';
	}
	
	float amount = stof(inputAmount);

	auto roundToTwoDecimalPlaces = [](float value) {
		return roundf(value * 100) / 100.0f;				// Rounds to two decimal places
	};

	float amountRounded = roundToTwoDecimalPlaces(amount);
	income.setAmount(amountRounded);

	char dayChoice;
	bool flag = true;
	do {
		//system("cls");
		cout << "Add transaction with today's date? (Select 'Y' or 'N')" << endl;
		dayChoice = AuxillaryFunctions::readChar();

		if (dayChoice == 'Y' || dayChoice == 'y') {
			income.setDate(getTodaysDate());
			cout << "Transaction added succesfully with today's date. ";
			system("pause");
			flag = false;
		}

		else if (dayChoice == 'N' || dayChoice == 'n') {

			string inputDate;
			do {
				cout << "Enter requested date of transaction in format: YYYY-MM-DD: " << endl;
				inputDate = AuxillaryFunctions::readLine();

			} while (!(checkDateFormat(inputDate)));
		 
			int date = AuxillaryFunctions::eraseDashFromDate(inputDate);
			
			income.setDate(date);
			cout << "Transaction added succesfully with provided date. ";
			system("pause");
			flag = false;
		}
		else cout << "Wrong input. Please select Y or N. " << endl;
		
	} while (flag);

    return income;
}

Expense OperationManager::gatherExpenseInfo() {

    Expense expense;
    expense.setTransactionID(expenseXML.getIDofLastIncome() + 1);
    expense.setUserID(LOGGED_ID);
    expense.setDate(LOGGED_ID);

    cout << "Enter item: " << endl;
    string itemInput = AuxillaryFunctions::readLine();
    expense.setItem(itemInput);

    cout << "Enter amount: " << endl;
    float amountInput = stof(AuxillaryFunctions::readLine());
    expense.setAmount(amountInput);

    return expense;
}

void OperationManager::showIncomes() {

    system("cls");
    if (incomes.empty()) { cout << "No incomes in your account. "; system("pause"); }

    else {
        cout << "Incomes in your account:" << endl << endl;
        for (Income income : incomes) {
            cout << "Income ID: "      << income.getTransactionID() << endl;
            cout << "User ID: " << income.getUserID()        << endl;
            cout << "Date: "    << AuxillaryFunctions::addDashToDate (income.getDate())          << endl;
            cout << "Item: "    << income.getItem()          << endl;
            cout << "Amount: "  << income.getAmount()        << endl << endl;
        }
        cout << endl;
		system("pause");
    }
}

void OperationManager::showExpenses() {

    system("cls");

    if (expenses.empty()) { 
		cout << "No expences in your account. ";
		system("pause");
	} else {
        cout << "Expenses in your account:" << endl << endl;
        for (Expense expense : expenses) {
            cout << "Expense ID: "      << expense.getTransactionID() << endl;
            cout << "User ID: " << expense.getUserID()        << endl;
            cout << "Date: "    << expense.getDate()          << endl;
            cout << "Item: "    << expense.getItem()          << endl;
            cout << "Amount: "  << expense.getAmount()        << endl << endl;
        }
        cout << endl;
		system("pause");
    }
}
void OperationManager::showBalance()
{
	int startDate = getTodaysDate() - elapsedDaysThisMonth();
	int endDate = getTodaysDate();


}
/*
int OperationManager::getRequestedDate(char day)
{
	std::time_t currentTime = std::time(nullptr);
	struct tm timeInfo;
	char timeBuffer[26];
	
	if (localtime_s(&timeInfo, &currentTime) == 0 && asctime_s(timeBuffer, sizeof(timeBuffer), &timeInfo) == 0) {
		std::cout << "Current time: " << timeBuffer << endl;
	} else {
		std::cout << "Error getting current time.";
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

	cout << dateString;
	int dateToday = stoi(dateString);
	
	if (day == 'Y' || day == 'y') return dateToday;

	if (day == 'N' || day == 'n') {

		cout << "Enter requested date in format: YYYY-MM-DD.";
		string inputDateWithDash = AuxillaryFunctions::readLine();

		if (inputDateWithDash.size() > 10) {
			cout << "Wrong input format. ";
			system("pause");
			return 0;
		}
		if (inputDateWithDash[4] != '-' || inputDateWithDash[6] != '-') {
			cout << "Wrong input format. ";
			system("pause");
			return 0;
		}
		if (inputDateWithDash[0] < 2) { // if year is less than 2000
			cout << "Cannot input date before 2000. ";
			system("pause");
			return 0;
		}

		char inputedDateArray[8];
		inputedDateArray[0] = inputDateWithDash[0];
		inputedDateArray[0] = inputDateWithDash[1];
		inputedDateArray[0] = inputDateWithDash[2];
		inputedDateArray[0] = inputDateWithDash[3];
		inputedDateArray[0] = inputDateWithDash[5];
		inputedDateArray[0] = inputDateWithDash[6];
		inputedDateArray[0] = inputDateWithDash[8];
		inputedDateArray[0] = inputDateWithDash[9];

		string inputedDateString = "";

		for (int i = 0; i < 8; i++)
			inputedDateString += inputedDateArray[i];

		int inputedDate = stoi(inputedDateString);

		if (inputedDate > dateToday) {
			cout << "Future dates are not acceptable. ";
			system("pause");
			return 0;
		}
		else return inputedDate;
	}
}
*/
int OperationManager::getTodaysDate()
{
	std::time_t currentTime = std::time(nullptr);
	struct tm timeInfo;
	char timeBuffer[26];

	if (localtime_s(&timeInfo, &currentTime) == 0 && asctime_s(timeBuffer, sizeof(timeBuffer), &timeInfo) == 0) {
		//std::cout << "Current time: " << timeBuffer << endl;
	}
	else {
		std::cout << "Error getting todays date.";
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

int OperationManager::getInputedDate()
{
	system("cls");
	cout << "Enter requested date of transaction in format: YYYY-MM-DD." << endl;
	string inputDateWithDash;
	bool flag = true;
	
	while (flag) {
		inputDateWithDash = AuxillaryFunctions::readLine();

		if (inputDateWithDash.size() < 10) {
			cout << "Wrong input format. ";
			system("pause");
		}
		if (inputDateWithDash[4] != '-' || inputDateWithDash[6] != '-') {
			cout << "Wrong input format. ";
			system("pause");
		}
		if (inputDateWithDash[0] < 2) { // if year is less than 2000
			cout << "Cannot input date before 2000. ";
			system("pause");
		}

	}

	char inputedDateArray[8];
	inputedDateArray[0] = inputDateWithDash[0];
	inputedDateArray[0] = inputDateWithDash[1];
	inputedDateArray[0] = inputDateWithDash[2];
	inputedDateArray[0] = inputDateWithDash[3];
	inputedDateArray[0] = inputDateWithDash[5];
	inputedDateArray[0] = inputDateWithDash[6];
	inputedDateArray[0] = inputDateWithDash[8];
	inputedDateArray[0] = inputDateWithDash[9];

	string inputedDateString = "";

	for (int i = 0; i < 8; i++)
		inputedDateString += inputedDateArray[i];

	int inputedDate = stoi(inputedDateString);
	return inputedDate;
}

bool OperationManager::checkDateFormat(string userInputDate)
{
	if (userInputDate.size() != 10)								// check input isnt to long to be ok
	{
		cout << "Wrong input format(incorrect input size). " << endl;
		return false;
	}
	if (userInputDate[4] != '-' || userInputDate[7] != '-') {	// check if seperated properly by '-' symbols in the right place
		cout << "Wrong input format(incorrect date seperation). " << endl;
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

	for (int i = 0; i < 8; i++) {							
		if (!(isdigit(dateArray[i]))) {							// check if input is made of digits only
			cout << "Wrong input format. " << endl;
			return false;
		}
	}

	string yearString = "";										// check year part of inputed string ([XXXX]-MM-DD)
	for (int i = 0; i < 4; i++)
		yearString += dateArray[i];
	 
	int yearInt = stoi(yearString);
	if (yearInt < 2000) {
		cout << "Cannot enter year less then 2000. " << endl;
		return false;
	}

	string monthString = "";									// check month part of inputed string (YYYY-[XX]-DD)
	monthString += dateArray[4];
	monthString += dateArray[5];
	int monthInt = stoi(monthString);
	if (monthInt > 12) {
		cout << "Invalid month. " << endl;
		return false;
	}

	string dayString = "";										// check day part of inputed string (YYYY-MM-[XX])
	dayString += dateArray[6];
	dayString += dateArray[7];
	int dayInt = stoi(dayString);
	if (dayInt > 31) {
		cout << "Invalid day. " << endl;
		return false;
	}

	string dateString = yearString + monthString + dayString;
	int dateInt = stoi(dateString);
	if (dateInt > getTodaysDate())								// check if inputed date isnt a future date
	{
		cout << "Can't input future date. " << endl;
		return false;
	}
	return true;
}

bool OperationManager::checkAmountFormat(string inputAmount)
{
	for (size_t i = 0; i < inputAmount.size(); i++) {	 // check string for forbidden characters
		if (!(isdigit(inputAmount[i])) && inputAmount[i] != ',' && inputAmount[i] != '.') {
			cout << "Wrong input format. " << endl;
			system("pause");
			return false;
		}
	}

	for (size_t i = 0; i < inputAmount.size(); i++){      // change all commas to dots
		if (inputAmount[i] == ',') inputAmount[i] = '.';
	}
	
	int dotCounter = 0;
	for (size_t i = 0; i < inputAmount.size(); i++) {	  // check string for too many dots
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
	
	for (size_t i = dotPlace+3; i < inputAmount.size(); i++) {	// decimals smaller then 0.01 forbidden
		if (inputAmount[i] != 0) {
			cout << "Wrong input format. 0.01 is smallest money resolution. " << endl;
			system("pause");
			return false;
		}
	}
	
	return true;
}
