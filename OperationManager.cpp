#include "OperationManager.h"
#include "AuxillaryFunctions.h"

void OperationManager::addTransaction(transactionType transactionType)
{
	system("cls");
	Transaction transaction = gatherTransactionInfo(transactionType);
	
	if (transactionType == INCOME) incomeXML.appendTransactionToXML(transaction);
	if (transactionType == EXPENSE)	expenseXML.appendTransactionToXML(transaction);
}

void OperationManager::showBalance(timePeriod timePeriod)
{
	system("cls");
	int startDate;
	int endDate;

	switch (timePeriod) {
	case THIS_MONTH:
		startDate = AuxillaryFunctions::getTodaysDate() - AuxillaryFunctions::elapsedDaysThisMonth();
		endDate = AuxillaryFunctions::getTodaysDate();
		break;

	case PREVIOUS_MONTH:
		startDate = AuxillaryFunctions::getTodaysDate() - AuxillaryFunctions::elapsedDaysThisMonth() - 100;
		endDate = AuxillaryFunctions::getTodaysDate() - AuxillaryFunctions::elapsedDaysThisMonth();
		break;

	case CUSTOM_PERIOD:

		string inputDate = "";
		do {
			cout << "Enter start of time period in format: YYYY-MM-DD: " << endl;
			inputDate = AuxillaryFunctions::readLine();

		} while (!(AuxillaryFunctions::checkDateFormat(inputDate)));

		startDate = AuxillaryFunctions::eraseDashesFromDate(inputDate);

		do {
			cout << "Enter end of time period in format: YYYY-MM-DD: " << endl;
			inputDate = AuxillaryFunctions::readLine();

		} while (!(AuxillaryFunctions::checkDateFormat(inputDate)));

		endDate = AuxillaryFunctions::eraseDashesFromDate(inputDate);

		if (endDate < startDate) {
			cout << "Inputed end date is before the start date. Please input correct dates. ";
			system("pause");
			return;
		}
		break;
	}
	
	incomes = incomeXML.uploadTransactionsFromXML(LOGGED_ID, startDate, endDate);
	expenses = expenseXML.uploadTransactionsFromXML(LOGGED_ID, startDate, endDate);

	sort(incomes.begin(), incomes.end(), [](const Transaction& lhs, const Transaction& rhs) {
		return lhs.getDate() < rhs.getDate(); });

	sort(expenses.begin(), expenses.end(), [](const Transaction& lhs, const Transaction& rhs) {
		return lhs.getDate() < rhs.getDate(); });

	float sumOfIncomes = 0.00;

	for (Transaction transaction : incomes)
		sumOfIncomes += transaction.getAmount();

	float sumOfExpenses = 0.00;

	for (Transaction transaction : expenses)
		sumOfExpenses += transaction.getAmount();

	system("cls");
	showTransactions(INCOME);
	cout << "Sum of incomes: " << fixed << setprecision(2) << sumOfIncomes << endl << endl << endl;

	showTransactions(EXPENSE);
	cout << "Sum of expenses: " << fixed << setprecision(2) << sumOfExpenses << endl << endl << endl;

	float balance = sumOfIncomes - sumOfExpenses;
	cout << "******************* End balance: *******************" << endl << endl << endl;
	cout << "Period Balace: " << fixed << setprecision(2) << balance << endl << endl << endl;
	system("pause");
}

Transaction OperationManager::gatherTransactionInfo(transactionType transactionType) {

	Transaction transaction;

	if (transactionType == INCOME) transaction.setTransactionID(incomeXML.getIDofLastTransaction() + 1);
	if (transactionType == EXPENSE) transaction.setTransactionID(expenseXML.getIDofLastTransaction() + 1);

	transaction.setUserID(LOGGED_ID);

	system("cls");
	string itemInput = "";
	cout << "Enter item: " << endl;
	itemInput = AuxillaryFunctions::readLine();
	transaction.setItem(itemInput);

	string inputAmount = "";
	do {
		cout << "Enter amount: " << endl;
		inputAmount = AuxillaryFunctions::readLine();
		
	} while (!(AuxillaryFunctions::checkAmountFormat(inputAmount)));
	
	
	for (size_t i = 0; i < inputAmount.size(); i++) {      // change comma to dot
		if (inputAmount[i] == ',') inputAmount[i] = '.';
	}
	
	float amount = stof(inputAmount);

	auto roundToTwoDecimalPlaces = [](float value) {
		return roundf(value * 100) / 100.0f;				// Rounds to two decimal places
	};

	float amountRounded = roundToTwoDecimalPlaces(amount);
	transaction.setAmount(amountRounded);

	char dayChoice;
	bool flag = true;
	do {
		//system("cls");
		cout << "Add transaction with today's date? (Select 'Y' or 'N')" << endl;
		dayChoice = AuxillaryFunctions::readChar();

		if (dayChoice == 'Y' || dayChoice == 'y') {
			transaction.setDate(AuxillaryFunctions::getTodaysDate());
			cout << "Transaction added succesfully with today's date. ";
			system("pause");
			flag = false;
		}

		else if (dayChoice == 'N' || dayChoice == 'n') {

			string inputDate;
			do {
				cout << "Enter requested date of transaction in format: YYYY-MM-DD: " << endl;
				inputDate = AuxillaryFunctions::readLine();

			} while (!(AuxillaryFunctions::checkDateFormat(inputDate)));
		 
			int date = AuxillaryFunctions::eraseDashesFromDate(inputDate);
			
			transaction.setDate(date);
			cout << "Transaction added succesfully with provided date. ";
			system("pause");
			flag = false;
		}
		else cout << "Wrong input. Please select Y or N. " << endl;
		
	} while (flag);

    return transaction;
}

void OperationManager::showTransactions(transactionType transactionType) {

	switch (transactionType)
	{

	case INCOME:

		if (incomes.empty())  cout << "No incomes in this time period. ";

		else {
			cout << "********************* Incomes: **********************" << endl << endl;
			for (Transaction transaction : incomes) {
				//cout << "Income ID: "      << income.getTransactionID() << endl;
				//cout << "User ID: " << income.getUserID()        << endl;
				cout << "_________________" << endl;
				cout << "Date: " << AuxillaryFunctions::addDashesToDate(transaction.getDate()) << endl;
				cout << "Item: " << transaction.getItem() << endl;
				cout << "Amount: " << fixed << setprecision(2) << transaction.getAmount() << endl;
			}
			cout << "_________________";
			cout << endl << endl << endl;
		}
		break;

	case EXPENSE:

		if (expenses.empty()) cout << "No expenses in this time period. ";

		else {
			cout << "******************** Expenses: *********************" << endl << endl;
			for (Transaction transaction : expenses) {
				//cout << "Expense ID: "      << expense.getTransactionID() << endl;
				//cout << "User ID: " << expense.getUserID()        << endl;
				cout << "_________________" << endl;
				cout << "Date: " << AuxillaryFunctions::addDashesToDate(transaction.getDate()) << endl;
				cout << "Item: " << transaction.getItem() << endl;
				cout << "Amount: " << fixed << setprecision(2) << transaction.getAmount() << endl;
			}
			cout << "_________________";
			cout << endl << endl << endl;
		}
	}
}

