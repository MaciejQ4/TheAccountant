#pragma once

#include "OperationXML.h"

class OperationManager
{
private:

	const int LOGGED_ID;
	
	vector<Income> incomes;
	OperationXML incomeXML;
	
	vector<Expense> expenses;
	OperationXML expenseXML;

	Expense gatherExpenseInfo();

public:

	OperationManager(string NAME_OF_INCOME_XML, string NAME_OF_EXPENSE_XML, int loggedID)
		: incomeXML(NAME_OF_INCOME_XML), expenseXML(NAME_OF_EXPENSE_XML), LOGGED_ID(loggedID)
	{
		incomes = incomeXML.uploadTransactionsFromXML(LOGGED_ID);
		expenses = expenseXML.uploadTransactionsFromXML(LOGGED_ID);
	}

	void addTransaction();
	void showTransactions();


};
