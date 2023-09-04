#pragma once

#include "UserManager.h"
#include "OperationManager.h"
#include "AuxillaryFunctions.h"

#include <ctime>
#include <time.h>
#include <iomanip>
#include <chrono>

class Accountant
{
private:

	UserManager userManager;
	OperationManager* operationManager;
	const string NAME_OF_INCOME_XML;
	const string NAME_OF_EXPENSE_XML;

public:

	Accountant(string nameOfUserXML, string NAME_OF_INCOME_XML, string NAME_OF_EXPENSE_XML) :
		userManager(nameOfUserXML), NAME_OF_INCOME_XML(NAME_OF_INCOME_XML), NAME_OF_EXPENSE_XML(NAME_OF_EXPENSE_XML)
	{
		operationManager = NULL;
	};

	bool isUserLogged();
	void createUser();
	void loginUser();
	void showAllUsers();
	void logOut();

	void showCurrentTime();
	void calculateTimeDifference();
	void howManyDays();

	void createTransaction();
	void showTransactions();
};

