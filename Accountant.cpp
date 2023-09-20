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

void Accountant::createTransaction(transactionType transactionType) {

	operationManager->addTransaction(transactionType);
}

void Accountant::showBalance(timePeriod timePeriod) {

	operationManager->showBalance(timePeriod);
}

void Accountant::changePassword() {

	userManager.changePassword();
}

void Accountant::logOut() {

	userManager.logOut();
}