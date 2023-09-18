#include "OperationManager.h"
#include "AuxillaryFunctions.h"

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
}

void OperationManager::showBalance(string timePeriod)
{
	system("cls");
	int startDate;
	int endDate;

	if (timePeriod == "THIS MONTH") {
		startDate = getTodaysDate() - elapsedDaysThisMonth();
		endDate = getTodaysDate();
	}

	else if (timePeriod == "PREVIOUS MONTH") {
		startDate = getTodaysDate() - elapsedDaysThisMonth() - 100;
		endDate = getTodaysDate() - elapsedDaysThisMonth();
	}

	else {

		string inputDate = "";
		do {
			cout << "Enter start of time period in format: YYYY-MM-DD: " << endl;
			inputDate = AuxillaryFunctions::readLine();

		} while (!(checkDateFormat(inputDate)));

		startDate = AuxillaryFunctions::eraseDashesFromDate(inputDate);

		do {
			cout << "Enter end of time period in format: YYYY-MM-DD: " << endl;
			inputDate = AuxillaryFunctions::readLine();

		} while (!(checkDateFormat(inputDate)));

		endDate = AuxillaryFunctions::eraseDashesFromDate(inputDate);

		if (endDate < startDate) {
			cout << "Inputed end date is before the start date. Please input correct dates. ";
			system("pause");
			return;
		}
	}

	incomes = incomeXML.uploadIncomesFromXML(LOGGED_ID, startDate, endDate);
	expenses = expenseXML.uploadExpensesFromXML(LOGGED_ID, startDate, endDate);

	sort(incomes.begin(), incomes.end(), [](const Income& lhs, const Income& rhs) {
		return lhs.getDate() < rhs.getDate(); });

	sort(expenses.begin(), expenses.end(), [](const Expense& lhs, const Expense& rhs) {
		return lhs.getDate() < rhs.getDate(); });

	float sumOfIncomes = 0;

	for (Income income : incomes)
		sumOfIncomes += income.getAmount();

	float sumOfExpenses = 0;

	for (Expense expense : expenses)
		sumOfExpenses += expense.getAmount();

	system("cls");
	showIncomes();
	cout << "Sum of incomes: " << sumOfIncomes << endl << endl << endl;

	showExpenses();
	cout << "Sum of expenses: " << sumOfExpenses << endl << endl << endl;

	float balance = sumOfIncomes - sumOfExpenses;
	cout << "******************* End balance: *******************" << endl << endl << endl;
	cout << "Balance for the period: " << balance << endl << endl << endl;
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
		 
			int date = AuxillaryFunctions::eraseDashesFromDate(inputDate);
			
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

	expense.setTransactionID(expenseXML.getIDofLastExpense() + 1);
	expense.setUserID(LOGGED_ID);

	system("cls");
	string itemInput = "";
	cout << "Enter item: " << endl;
	itemInput = AuxillaryFunctions::readLine();
	expense.setItem(itemInput);

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
	expense.setAmount(amountRounded);

	char dayChoice;
	bool flag = true;
	do {
		//system("cls");
		cout << "Add transaction with today's date? (Select 'Y' or 'N')" << endl;
		dayChoice = AuxillaryFunctions::readChar();

		if (dayChoice == 'Y' || dayChoice == 'y') {
			expense.setDate(getTodaysDate());
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

			int date = AuxillaryFunctions::eraseDashesFromDate(inputDate);

			expense.setDate(date);
			cout << "Transaction added succesfully with provided date. ";
			system("pause");
			flag = false;
		}
		else cout << "Wrong input. Please select Y or N. " << endl;

	} while (flag);

	return expense;
}

void OperationManager::showIncomes() {

    //system("cls");
    if (incomes.empty())  cout << "No incomes in this time period. ";

    else {
        cout << "********************* Incomes: **********************" << endl << endl;
        for (Income income : incomes) {
            //cout << "Income ID: "      << income.getTransactionID() << endl;
            //cout << "User ID: " << income.getUserID()        << endl;
			cout << "_________________" << endl;
			cout << "Date: "    << AuxillaryFunctions::addDashesToDate (income.getDate())          << endl;
            cout << "Item: "    << income.getItem()          << endl;
            cout << "Amount: "  << income.getAmount()        << endl;
        }
		cout << "_________________";
		cout << endl << endl << endl;
    }
}

void OperationManager::showExpenses() {

    //system("cls");
    if (expenses.empty()) cout << "No expenses in this time period. ";
		
	 else {
        cout << "******************** Expenses: *********************" << endl << endl;
        for (Expense expense : expenses) {
            //cout << "Expense ID: "      << expense.getTransactionID() << endl;
            //cout << "User ID: " << expense.getUserID()        << endl;
			cout << "_________________" << endl;
			cout << "Date: " << AuxillaryFunctions::addDashesToDate(expense.getDate()) << endl;
            cout << "Item: "    << expense.getItem()          << endl;
            cout << "Amount: "  << expense.getAmount()        << endl;
        }
		cout << "_________________";
		cout << endl << endl << endl;
    }
}

int OperationManager::getTodaysDate()
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

int OperationManager::elapsedDaysThisMonth() {

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

bool OperationManager::checkDateFormat(string userInputDate)
{
	if (userInputDate.size() != 10){							// check input isnt to long to be ok
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

	for (size_t i = 0; i < 8; i++) {
		if (!(isdigit(dateArray[i]))) {							// check if input is made of digits only
			cout << "Wrong input format. " << endl;
			return false;
		}
	}

	string yearString = "";										// check year part of inputed string ([XXXX]-MM-DD)
	for (size_t i = 0; i < 4; i++)
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
	if (dateInt > getTodaysDate())	{						   // check if inputed date isnt a future date{
		cout << "Can't input future date. " << endl;
		return false;
	}
	return true;
}

bool OperationManager::checkAmountFormat(string inputAmount)
{
	for (size_t i = 0; i < inputAmount.size(); i++) {		  // check string for forbidden characters
		if (!(isdigit(inputAmount[i])) && inputAmount[i] != ',' && inputAmount[i] != '.') {
			cout << "Wrong input format. ";
			system("pause");
			return false;
		}
	}

	for (size_t i = 0; i < inputAmount.size(); i++){		  // change all commas to dots
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
	
	for (size_t i = dotPlace+3; i < inputAmount.size(); i++) {	// decimals smaller then 0.01 forbidden
		if (inputAmount[i] != 0) {
			cout << "Wrong input format. 0.01 is smallest resolution for transaction amount. " << endl;
			system("pause");
			return false;
		}
	}
	return true;
}