#pragma once

#include "XML.h"
#include "Transaction.h"

class OperationXML : protected XML
{
private:

	int IDofLastTransaction;

public:

	OperationXML(string NAME_OF_XML) : XML(NAME_OF_XML)
	{
		IDofLastTransaction = 0;
	};

	int getIDofLastTransaction();
	vector<Transaction> uploadTransactionsFromXML(int LOGGED_ID, int startDate, int endDate);
	void appendTransactionToXML(Transaction transaction);
};

