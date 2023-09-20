#include "OperationManager.h"
#include "AuxillaryFunctions.h"

void OperationManager::addTransaction(transactionType transactionType)
{
	system("cls");
	Transaction transaction = gatherIncomeInfo();
	
	switch (transactionType) {

	case INCOME:
		incomes.push_back(transaction);
		incomeXML.appendTransactionToXML(transaction);
		break;

	case EXPENSE:
		expenses.push_back(transaction);
		expenseXML.appendTransactionToXML(transaction);
		break;
	}
}

void OperationManager::showBalance(timePeriod timePeriod)
{
	system("cls");
	int startDate;
	int endDate;

	switch (timePeriod) {
	case THIS_MONTH:
		startDate = getTodaysDate() - elapsedDaysThisMonth();
		endDate = getTodaysDate();
		break;


	case PREVIOUS_MONTH:
		startDate = getTodaysDate() - elapsedDaysThisMonth() - 100;
		endDate = getTodaysDate() - elapsedDaysThisMonth();
		break;


	case CUSTOM_PERIOD:

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
		break;
	}
	
	incomes = incomeXML.uploadTransactionsFromXML(LOGGED_ID, startDate, endDate);
	expenses = expenseXML.uploadTransactionsFromXML(LOGGED_ID, startDate, endDate);

	sort(incomes.begin(), incomes.end(), [](const Transaction& lhs, const Transaction& rhs) {
		return lhs.getDate() < rhs.getDate(); });

	sort(expenses.begin(), expenses.end(), [](const Transaction& lhs, const Transaction& rhs) {
		return lhs.getDate() < rhs.getDate(); });

	float sumOfIncomes = 0.00;

	for (Transaction transaction : incomes)
		sumOfIncomes += transaction.getAmount();

	float sumOfExpenses = 0.00;

	for (Transaction transaction : expenses)
		sumOfExpenses += transaction.getAmount();

	system("cls");
	showIncomes();
	cout << "Sum of incomes: " << fixed << setprecision(2) << sumOfIncomes << endl << endl << endl;

	showExpenses();
	cout << "Sum of expenses: " << fixed << setprecision(2) << sumOfExpenses << endl << endl << endl;

	float balance = sumOfIncomes - sumOfExpenses;
	cout << "******************* End balance: *******************" << endl << endl << endl;
	cout << "Period Balace: " << fixed << setprecision(2) << balance << endl << endl << endl;
	system("pause");
}

Transaction OperationManager::gatherIncomeInfo() {

	Transaction transaction;

	transaction.setTransactionID(incomeXML.getIDofLastTransaction() + 1);
	transaction.setUserID(LOGGED_ID);

	system("cls");
	string itemInput = "";
	cout << "Enter item: " << endl;
	itemInput = AuxillaryFunctions::readLine();
	transaction.setItem(itemInput);

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
	transaction.setAmount(amountRounded);

	char dayChoice;
	bool flag = true;
	do {
		//system("cls");
		cout << "Add transaction with today's date? (Select 'Y' or 'N')" << endl;
		dayChoice = AuxillaryFunctions::readChar();

		if (dayChoice == 'Y' || dayChoice == 'y') {
			transaction.setDate(getTodaysDate());
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
			
			transaction.setDate(date);
			cout << "Transaction added succesfully with provided date. ";
			system("pause");
			flag = false;
		}
		else cout << "Wrong input. Please select Y or N. " << endl;
		
	} while (flag);

    return transaction;
}

Transaction OperationManager::gatherExpenseInfo() {

	Transaction transaction;

	transaction.setTransactionID(expenseXML.getIDofLastTransaction() + 1);
	transaction.setUserID(LOGGED_ID);

	system("cls");
	string itemInput = "";
	cout << "Enter item: " << endl;
	itemInput = AuxillaryFunctions::readLine();
	transaction.setItem(itemInput);

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
	transaction.setAmount(amountRounded);

	char dayChoice;
	bool flag = true;
	do {
		//system("cls");
		cout << "Add transaction with today's date? (Select 'Y' or 'N')" << endl;
		dayChoice = AuxillaryFunctions::readChar();

		if (dayChoice == 'Y' || dayChoice == 'y') {
			transaction.setDate(getTodaysDate());
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

			transaction.setDate(date);
			cout << "Transaction added succesfully with provided date. ";
			system("pause");
			flag = false;
		}
		else cout << "Wrong input. Please select Y or N. " << endl;

	} while (flag);

	return transaction;
}

void OperationManager::showIncomes() {

    //system("cls");
    if (incomes.empty())  cout << "No incomes in this time period. ";

    else {
        cout << "********************* Incomes: **********************"	<< endl << endl;
        for (Transaction transaction : incomes) {
            //cout << "Income ID: "      << income.getTransactionID() << endl;
            //cout << "User ID: " << income.getUserID()        << endl;
			cout << "_________________"																	<< endl;
			cout << "Date: "    << AuxillaryFunctions::addDashesToDate (transaction.getDate())          << endl;
            cout << "Item: "    << transaction.getItem()												<< endl;
            cout << "Amount: "  << fixed << setprecision(2) << transaction.getAmount()					<< endl;
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
        for (Transaction transaction : expenses) {
            //cout << "Expense ID: "      << expense.getTransactionID() << endl;
            //cout << "User ID: " << expense.getUserID()        << endl;
			cout << "_________________"																<< endl;
			cout << "Date: "	<< AuxillaryFunctions::addDashesToDate(transaction.getDate())		<< endl;
            cout << "Item: "    << transaction.getItem()											<< endl;
            cout << "Amount: "  << fixed << setprecision(2) << transaction.getAmount()				<< endl;
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
	if (userInputDate.size() != 10){							// check input isnt too long to be ok
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
	if (date > getTodaysDate())	{						   // check if inputed date isnt a future date
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
	
	for (size_t i = 0; i < inputAmount.size(); i++) {
		char ch = inputAmount[i];
		if (i == dotPlace && ch == '0') {
			cout << "Wrong input format. Leading zeros not allowed. " << endl;
			system("pause");
			return false;
		}
	}

	if (inputAmount.size() - dotPlace > 3) { 
		cout << "Wrong input format. More than two decimal places not allowed.";
		system("pause");
		return false;
	}
	return true;
}