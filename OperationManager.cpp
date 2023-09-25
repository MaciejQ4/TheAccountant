#include "OperationManager.h"
#include "AuxillaryFunctions.h"

void OperationManager::addTransaction(TransactionType transactionType)
{
	system("cls");
	Transaction transaction = gatherTransactionInfo(transactionType);
	
	if (transactionType == INCOME) {
		incomeXML.appendTransactionToXML(transaction);
		incomes.push_back(transaction);
	}

	if (transactionType == EXPENSE) {
		expenseXML.appendTransactionToXML(transaction);
		expenses.push_back(transaction);
	}
}

void OperationManager::showBalance(TimePeriod timePeriod)
{
	system("cls");
	int startDate = 0;
	int endDate = 0;

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

	sort(incomes.begin(), incomes.end(), [](const Transaction& lhs, const Transaction& rhs) {
		return lhs.getDate() < rhs.getDate(); });

	sort(expenses.begin(), expenses.end(), [](const Transaction& lhs, const Transaction& rhs) {
		return lhs.getDate() < rhs.getDate(); });

	float sumOfIncomes = calcluateIncomes(startDate, endDate);
	float sumOfExpenses = calcluateExpenses(startDate, endDate);
	
	system("cls");
	showTransactions(INCOME, startDate, endDate);
	cout << "Sum of incomes: " << fixed << setprecision(2) << sumOfIncomes << endl << endl << endl;

	showTransactions(EXPENSE,startDate, endDate);
	cout << "Sum of expenses: " << fixed << setprecision(2) << sumOfExpenses << endl << endl << endl;

	float balance = sumOfIncomes - sumOfExpenses;
	cout << "******************** End balance: *******************" << endl << endl << endl;
	cout << "Period Balace: " << fixed << setprecision(2) << balance << endl << endl << endl;
	system("pause");
}

Transaction OperationManager::gatherTransactionInfo(TransactionType transactionType) {

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
		for (size_t i = 0; i < inputAmount.size(); i++) {
			if (inputAmount[i] == ',') inputAmount[i] = '.';
		}

	} while (!(AuxillaryFunctions::checkAmountFormat(inputAmount)));
	
	float amount = stof(inputAmount);
	transaction.setAmount(amount);

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

float OperationManager::calcluateIncomes(int startDate, int endDate)
{
	float sumOfIncomes = 0.00;
	
	for (Transaction transaction : incomes) {
		if (LOGGED_ID == transaction.getUserID() && transaction.getDate() <= endDate && transaction.getDate() >= startDate )
			sumOfIncomes += transaction.getAmount();
	}
	return sumOfIncomes;
}

float OperationManager::calcluateExpenses(int startDate, int endDate)
{
	float sumOfExpenses = 0.00;

	for (Transaction transaction : expenses) {
		if (LOGGED_ID == transaction.getUserID() && transaction.getDate() <= endDate && transaction.getDate() >= startDate )
			sumOfExpenses += transaction.getAmount();
	}
	return sumOfExpenses;
}

void OperationManager::showTransactions(TransactionType transactionType, int startDate, int endDate) {

	string description = transactionType == INCOME ? " Incomes:" : "Expenses:";
	vector<Transaction> vector = transactionType == INCOME ? incomes : expenses;

	if (vector.empty())  cout << "No  " << description << " in this time period. ";

	else {
		cout << "********************* " << description << " *********************"    << endl << endl;
		for (Transaction transaction : vector) {
			if (transaction.getDate() <= endDate && transaction.getDate() >= startDate) {

				cout << "_________________"													   << endl;
				cout << "Date: " << AuxillaryFunctions::addDashesToDate(transaction.getDate()) << endl;
				cout << "Item: " << transaction.getItem() << endl;
				cout << "Amount: " << fixed << setprecision(2) << transaction.getAmount()      << endl;
			}
		}
		cout << "_________________";
		cout << endl << endl << endl;
	}
}