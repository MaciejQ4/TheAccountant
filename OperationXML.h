#pragma once
#include "XML.h"
#include "Income.h"
#include "Expense.h"

class OperationXML : protected XML
{
	int IDofLastIncome;
	int IDofLastExpense;


public:
	OperationXML(string NAME_OF_XML) : XML(NAME_OF_XML)
	{
		IDofLastIncome = 0;
		IDofLastExpense = 0;
	};

	int getIDofLastIncome();
	int getIDofLastExpense();

	vector<Income> uploadIncomesFromXML(int LOGGED_ID, int startDate, int endDate);
	vector<Expense> uploadExpensesFromXML(int LOGGED_ID, int startDate, int endDate);
	void appendTransactionToXML(Transaction transaction);
};

