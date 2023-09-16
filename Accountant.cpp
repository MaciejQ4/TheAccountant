#include "Accountant.h"

bool Accountant::isUserLogged() {

	return userManager.isUserLogged();
}

void Accountant::createUser() {

	userManager.createUser();
}

void Accountant::loginUser() {

	userManager.loginUser();
	if (userManager.isUserLogged()) {
		operationManager = new OperationManager(NAME_OF_INCOME_XML, NAME_OF_EXPENSE_XML, userManager.getLoggedID());
	}
}

void Accountant::showAllUsers() {

	userManager.showAllUsers();
}

void Accountant::logOut() {

	userManager.logOut();
}

void Accountant::showCurrentTime() {

	operationManager->showCurrentTime();
}

void Accountant::calculateTimeDifference() {

	operationManager->calculateTimeDifference();
}


void Accountant::howManyDays() {

	operationManager->elapsedDaysThisMonth();
}

void Accountant::createIncome()
{
	operationManager->addIncome();
}

void Accountant::showIncomes()
{
	operationManager->showIncomes();
}

void Accountant::createExpense()
{
	operationManager->addExpense();
}

void Accountant::showExpenses()
{
	operationManager->showExpenses();
}

void Accountant::showBalance() {

	operationManager->showBalance();
}