#pragma once

#include "OperationXML.h"

#include <ctime>
#include <time.h>
#include <iomanip>
#include <chrono>
#include "VariationEnums.h"

class OperationManager
{
private:

	const int LOGGED_ID;
	
	vector<Transaction> incomes;
	OperationXML incomeXML;
	
	vector<Transaction> expenses;
	OperationXML expenseXML;

	Transaction gatherIncomeInfo();
	Transaction gatherExpenseInfo();

	void showIncomes();
	void showExpenses();

	int getTodaysDate();
	int elapsedDaysThisMonth();

	bool checkDateFormat(string userInputDate); // auxillary ?
	bool checkAmountFormat(string userInputAmount);  // auxillary ?

public:

	OperationManager(string NAME_OF_INCOME_XML, string NAME_OF_EXPENSE_XML, int loggedID)
		: incomeXML(NAME_OF_INCOME_XML), expenseXML(NAME_OF_EXPENSE_XML), LOGGED_ID(loggedID)
	{
	}

	void addIncome();
	void addExpense();
	void showBalance(timePeriod timePeriod);
};
