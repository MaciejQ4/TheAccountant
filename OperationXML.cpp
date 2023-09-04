#include "OperationXML.h"

int OperationXML::getIDofLastTransaction() {

    return IDofLastTransaction;
}

vector<Transaction> OperationXML::uploadTransactionsFromXML(int LOGGED_ID)
{
    vector<Transaction> trancactions;
    TiXmlDocument doc;

    if (doc.LoadFile(getFileName().c_str())) {
        TiXmlElement* root = doc.RootElement();
        if (!root) {
            std::cout << "Error: Root element not found in Expense XML." << std::endl;
            return trancactions;
        }

        for (TiXmlElement* ExpenseElement = root->FirstChildElement("Expense"); ExpenseElement; ExpenseElement = ExpenseElement->NextSiblingElement("Expense")) {
            int TransactionID = 0;
            int userID = 0;
            int date = 0;
            string item = "";
            int amount = 0;

            TiXmlElement* ExpenseIDElement = ExpenseElement->FirstChildElement("ExpenseID");
            if (ExpenseIDElement) {
                const char* ExpenseIDText = ExpenseIDElement->GetText();
                if (ExpenseIDText)
                    TransactionID = std::stoi(ExpenseIDText);
            }

            TiXmlElement* userIDElement_Expense = ExpenseElement->FirstChildElement("UserID");
            if (userIDElement_Expense) {
                const char* UserIDText = userIDElement_Expense->GetText();
                if (UserIDText)
                    userID = stoi(UserIDText);
            }

            TiXmlElement* DateElement_Expense = ExpenseElement->FirstChildElement("Date");
            if (DateElement_Expense) {
                const char* DateText = DateElement_Expense->GetText();
                if (DateText)
                    date = stoi(DateText);
            }

            TiXmlElement* ItemElement_Expense = ExpenseElement->FirstChildElement("Item");
            if (ItemElement_Expense) {
                const char* ItemText_Expense = ItemElement_Expense->GetText();
                if (ItemText_Expense)
                    item = ItemText_Expense;
            }

            TiXmlElement* AmountElement_Expense = ExpenseElement->FirstChildElement("Amount");
            if (AmountElement_Expense) {
                const char* AmountText = AmountElement_Expense->GetText();
                if (AmountText)
                    amount = stoi(AmountText);
            }

            if (TransactionID > IDofLastTransaction) IDofLastTransaction = TransactionID;
            
            if (userID == LOGGED_ID) {
                Transaction transaction;
                transaction.setTransactionID(TransactionID);
                transaction.setUserID(userID);
                transaction.setDate(date);
                transaction.setItem(item);
                transaction.setAmount(amount);

                trancactions.push_back(transaction);
                }
        }
    }
    else {
        std::cout << "Error loading Expense XML file." << std::endl;
    }
    return trancactions;
}

void OperationXML::appendTransactionToXML(Transaction transaction)
{
    TiXmlDocument doc;

    if (doc.LoadFile(getFileName().c_str()))
    {
        TiXmlElement* root = doc.RootElement();

        TiXmlElement* TransactionElement = new TiXmlElement("Transaction");
        root->LinkEndChild(TransactionElement);

        TiXmlElement* TransactionIDElement_Expense = new TiXmlElement("TransactionID");
        TransactionIDElement_Expense->LinkEndChild(new TiXmlText(std::to_string(transaction.getTransactionID()).c_str()));
        TransactionElement->LinkEndChild(TransactionIDElement_Expense);

        TiXmlElement* userIDElement_Expense = new TiXmlElement("UserID");
        userIDElement_Expense->LinkEndChild(new TiXmlText(std::to_string(transaction.getUserID()).c_str()));
        TransactionElement->LinkEndChild(userIDElement_Expense);

        TiXmlElement* DateElement_Expense = new TiXmlElement("Date");
        DateElement_Expense->LinkEndChild(new TiXmlText(std::to_string(transaction.getDate()).c_str()));
        TransactionElement->LinkEndChild(DateElement_Expense);

        TiXmlElement* ItemElement_Expense = new TiXmlElement("Item");
        ItemElement_Expense->LinkEndChild(new TiXmlText(transaction.getItem().c_str()));
        TransactionElement->LinkEndChild(ItemElement_Expense);

        TiXmlElement* AmountElement_Expense = new TiXmlElement("Amount");
        AmountElement_Expense->LinkEndChild(new TiXmlText(std::to_string(transaction.getAmount()).c_str()));
        TransactionElement->LinkEndChild(AmountElement_Expense);

        doc.SaveFile(getFileName().c_str());
        IDofLastTransaction++;
    }
    else
    {
        TiXmlElement* root = new TiXmlElement("Expenses");
        doc.LinkEndChild(root);

        TiXmlElement* TransactionElement = new TiXmlElement("Expense");
        root->LinkEndChild(TransactionElement);

        TiXmlElement* expenseIDElement_Expense = new TiXmlElement("ExpenseID");
        expenseIDElement_Expense->LinkEndChild(new TiXmlText(std::to_string(transaction.getTransactionID()).c_str()));
        TransactionElement->LinkEndChild(expenseIDElement_Expense);

        TiXmlElement* userIDElement_Expense = new TiXmlElement("UserID");
        userIDElement_Expense->LinkEndChild(new TiXmlText(std::to_string(transaction.getUserID()).c_str()));
        TransactionElement->LinkEndChild(userIDElement_Expense);

        TiXmlElement* DateElement_Expense = new TiXmlElement("Date");
        DateElement_Expense->LinkEndChild(new TiXmlText(std::to_string(transaction.getDate()).c_str()));
        TransactionElement->LinkEndChild(DateElement_Expense);

        TiXmlElement* ItemElement_Expense = new TiXmlElement("Item");
        ItemElement_Expense->LinkEndChild(new TiXmlText(transaction.getItem().c_str()));
        TransactionElement->LinkEndChild(ItemElement_Expense);

        TiXmlElement* AmountElement_Expense = new TiXmlElement("Amount");
        AmountElement_Expense->LinkEndChild(new TiXmlText(std::to_string(transaction.getAmount()).c_str()));
        TransactionElement->LinkEndChild(AmountElement_Expense);

        doc.SaveFile(getFileName().c_str());
        IDofLastTransaction++;
    }
}
