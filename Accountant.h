#pragma once

#include "UserManager.h"
#include "AuxillaryFunctions.h"

#include <ctime>
#include <time.h>
#include <iomanip>
#include <chrono>

class Accountant
{
private:

	UserManager userManager;

public:

	Accountant(string nameOfUserXML) :
		userManager(nameOfUserXML) {};

	bool isUserLogged();
	void createUser();
	void loginUser();
	void showAllUsers();
	void logOut();

	void showCurrentTime();
	void calculateTimeDifference();
	void howManyDays();
};

