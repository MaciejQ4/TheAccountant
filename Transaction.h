#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
using namespace std;

class Transaction
{
	int transactionID;
	int userID;
	int date;
	string item;
	int amount;

public:

	Transaction(int transactionID = 0, int userID = 0, int date = 0, string item = "", int amount = 0)
	{
		this->transactionID = transactionID;
		this->userID = userID;
		this->date = date;
		this->item = item;
		this->amount = amount;
	}

	int getTransactionID();
	int getUserID();
	int getDate();
	string getItem();
	int getAmount();

	void setTransactionID(int newID);
	void setUserID(int newID);
	void setDate(int newDate);
	void setItem(string newItem);
	void setAmount(int newAmount);

};

