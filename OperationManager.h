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

	Transaction gatherTransactionInfo(TransactionType transactionType);
	float calcluateIncomes(int startDate, int endDate);
	float calcluateExpenses(int startDate, int endDate);
	void showTransactions(TransactionType transactionType, int startDate, int endDate);

public:

	OperationManager(string NAME_OF_INCOME_XML, string NAME_OF_EXPENSE_XML, int loggedID)
		: incomeXML(NAME_OF_INCOME_XML), expenseXML(NAME_OF_EXPENSE_XML), LOGGED_ID(loggedID)
	{
		incomes = incomeXML.uploadTransactionsFromXML(LOGGED_ID);
		expenses = expenseXML.uploadTransactionsFromXML(LOGGED_ID);
	}

	void addTransaction(TransactionType transactionType);
	void showBalance(TimePeriod timePeriod);
};
