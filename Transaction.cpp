#include "Transaction.h"

int Transaction::getTransactionID() {

	return transactionID;
}

int Transaction::getUserID() {

	return userID;
}

int Transaction::getDate() const {

	return date;
}

string Transaction::getItem() {

	return item;
}

float Transaction::getAmount() {

	return amount;
}

void Transaction::setTransactionID(int newID) {

	if (newID >= 0)
		transactionID = newID;
}

void Transaction::setUserID(int newID) {

	userID = newID;
}

void Transaction::setDate(int newDate) {

	date = newDate;
}

void Transaction::setItem(string newItem) {

	item = newItem;
}

void Transaction::setAmount(float newAmount) {

	amount = newAmount;
}