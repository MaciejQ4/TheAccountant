#include "Accountant.h"

bool Accountant::isUserLogged() {

	return userManager.isUserLogged();
}

void Accountant::createUser() {

	userManager.createUser();
}

void Accountant::loginUser() {

	userManager.loginUser();
	if (userManager.isUserLogged()) {
		operationManager = new OperationManager(NAME_OF_INCOME_XML, NAME_OF_EXPENSE_XML, userManager.getLoggedID());
	}
}

void Accountant::showAllUsers() {

	userManager.showAllUsers();
}

void Accountant::logOut() {

	userManager.logOut();
}

void Accountant::showCurrentTime() {

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

void Accountant::calculateTimeDifference() {
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

void Accountant::howManyDays() {

	// Get the current date
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	std::tm timeInfo;

	// Use localtime_s for safer handling
	if (localtime_s(&timeInfo, &currentTime) != 0) {
		cout << "Failed to get local time." << endl;
		return;
	}

	// Days in each month (accounting for leap years)
	static const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int currentMonth = timeInfo.tm_mon + 1; // Adjust for zero-based indexing
	int currentYear = timeInfo.tm_year + 1900; // Adjust for year offset

	int days = daysInMonth[currentMonth];

	if (currentMonth == 2 && isLeapYear(currentYear)) {
		days++; // February has 29 days in a leap year
	}
	cout << days << endl;
	system("pause");
}

void Accountant::createTransaction()
{
	operationManager->addTransaction();
}

void Accountant::showTransactions()
{
	operationManager->showTransactions();
}
