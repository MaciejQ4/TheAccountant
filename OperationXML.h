#pragma once
#include "XML.h"
#include "Income.h"
#include "Expense.h"

class OperationXML : protected XML
{
	int IDofLastTransaction;


public:
	OperationXML(string NAME_OF_XML) : XML(NAME_OF_XML)
	{
		IDofLastTransaction = 0;
	};

	int getIDofLastTransaction();
	vector<Transaction> uploadTransactionsFromXML(int LOGGED_ID);
	void appendTransactionToXML(Transaction transaction);
};

