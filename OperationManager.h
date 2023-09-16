#pragma once

#include "OperationXML.h"

#include <ctime>
#include <time.h>
#include <iomanip>
#include <chrono>

class OperationManager
{
private:

	const int LOGGED_ID;
	
	vector<Income> incomes;
	OperationXML incomeXML;
	
	vector<Expense> expenses;
	OperationXML expenseXML;

	Income gatherIncomeInfo();
	Expense gatherExpenseInfo();

	//int getRequestedDate(char day);
	int getTodaysDate();
	int getInputedDate();
	bool checkDateFormat(string userInputDate);
	bool checkAmountFormat(string userInputAmount);
	

public:

	OperationManager(string NAME_OF_INCOME_XML, string NAME_OF_EXPENSE_XML, int loggedID)
		: incomeXML(NAME_OF_INCOME_XML), expenseXML(NAME_OF_EXPENSE_XML), LOGGED_ID(loggedID)
	{
		//incomes = incomeXML.uploadIncomesFromXML(LOGGED_ID);
		//expenses = expenseXML.uploadExpensesFromXML(LOGGED_ID);
	}

	void showCurrentTime();
	void calculateTimeDifference();
	int elapsedDaysThisMonth();
	
	void addIncome();
	void addExpense();

	void showIncomes();
	void showExpenses();

	void showBalance();


};
