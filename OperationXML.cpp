#include "OperationXML.h"

int OperationXML::getIDofLastIncome() {

    return IDofLastIncome;
}

int OperationXML::getIDofLastExpense()
{
    return IDofLastExpense;
}

vector<Income> OperationXML::uploadIncomesFromXML(int LOGGED_ID, int startDate, int endDate)
{
    vector<Income> incomes;
    TiXmlDocument doc;

    if (doc.LoadFile(getFileName().c_str())) {
        TiXmlElement* root = doc.RootElement();
        if (!root) {
            std::cout << "Error: Root element not found in Income XML." << std::endl;
            return incomes;
        }

        for (TiXmlElement* TransactionElement = root->FirstChildElement("Transaction"); TransactionElement; TransactionElement = TransactionElement->NextSiblingElement("Transaction")) {
            int TransactionID = 0;
            int userID = 0;
            int date = 0;
            string item = "";
            float amount = 0;

            TiXmlElement* TransactionIDElement = TransactionElement->FirstChildElement("TransactionID");
            if (TransactionIDElement) {
                const char* IncomeIDText = TransactionIDElement->GetText();
                if (IncomeIDText)
                    TransactionID = std::stoi(IncomeIDText);
            }

            TiXmlElement* userIDElement = TransactionElement->FirstChildElement("UserID");
            if (userIDElement) {
                const char* UserIDText = userIDElement->GetText();
                if (UserIDText)
                    userID = stoi(UserIDText);
            }

            TiXmlElement* DateElement = TransactionElement->FirstChildElement("Date");
            if (DateElement) {
                const char* DateText = DateElement->GetText();
                if (DateText)
                    date = stoi(DateText);
            }

            TiXmlElement* ItemElement = TransactionElement->FirstChildElement("Item");
            if (ItemElement) {
                const char* ItemText = ItemElement->GetText();
                if (ItemText)
                    item = ItemText;
            }

            TiXmlElement* AmountElement = TransactionElement->FirstChildElement("Amount");
            if (AmountElement) {
                const char* AmountText = AmountElement->GetText();
                if (AmountText)
                    amount = stof(AmountText);
            }

            if (TransactionID > IDofLastIncome) IDofLastIncome = TransactionID;
            
            Income transaction;
            transaction.setTransactionID(TransactionID);
            transaction.setUserID(userID);
            transaction.setDate(date);
            transaction.setItem(item);
            transaction.setAmount(amount);

            if (userID == LOGGED_ID && date >= startDate && date <= endDate) {
                incomes.push_back(transaction);
            }
        }
    }
    else {
        std::cout << "Error loading Income XML file." << std::endl;
    }
    return incomes;
}

vector<Expense> OperationXML::uploadExpensesFromXML(int LOGGED_ID, int startDate, int endDate)
{
    vector<Expense> expenses;
    TiXmlDocument doc;

    if (doc.LoadFile(getFileName().c_str())) {
        TiXmlElement* root = doc.RootElement();
        if (!root) {
            std::cout << "Error: Root element not found in Expense XML." << std::endl;
            return expenses;
        }

        for (TiXmlElement* TransactionElement = root->FirstChildElement("Expense"); TransactionElement; TransactionElement = TransactionElement->NextSiblingElement("Expense")) {
            int TransactionID = 0;
            int userID = 0;
            int date = 0;
            string item = "";
            float amount = 0;

            TiXmlElement* TransactionIDElement = TransactionElement->FirstChildElement("ExpenseID");
            if (TransactionIDElement) {
                const char* ExpenseIDText = TransactionIDElement->GetText();
                if (ExpenseIDText)
                    TransactionID = std::stoi(ExpenseIDText);
            }

            TiXmlElement* userIDElement = TransactionElement->FirstChildElement("UserID");
            if (userIDElement) {
                const char* UserIDText = userIDElement->GetText();
                if (UserIDText)
                    userID = stoi(UserIDText);
            }

            TiXmlElement* DateElement = TransactionElement->FirstChildElement("Date");
            if (DateElement) {
                const char* DateText = DateElement->GetText();
                if (DateText)
                    date = stoi(DateText);
            }

            TiXmlElement* ItemElement = TransactionElement->FirstChildElement("Item");
            if (ItemElement) {
                const char* ItemText = ItemElement->GetText();
                if (ItemText)
                    item = ItemText;
            }

            TiXmlElement* AmountElement = TransactionElement->FirstChildElement("Amount");
            if (AmountElement) {
                const char* AmountText = AmountElement->GetText();
                if (AmountText)
                    amount = stof(AmountText);
            }

            if (TransactionID > IDofLastExpense) IDofLastExpense = TransactionID;

       
                Expense transaction;
                transaction.setTransactionID(TransactionID);
                transaction.setUserID(userID);
                transaction.setDate(date);
                transaction.setItem(item);
                transaction.setAmount(amount);

                if (userID == LOGGED_ID  && date >= startDate && date <= endDate ) {
                    expenses.push_back(transaction);
                }
        }
    }
    else {
        std::cout << "Error loading Expense XML file." << std::endl;
    }
    return expenses;
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
        IDofLastIncome++;
    }
    else
    {
        TiXmlElement* root = new TiXmlElement("Transactions");
        doc.LinkEndChild(root);

        TiXmlElement* TransactionElement = new TiXmlElement("Transaction");
        root->LinkEndChild(TransactionElement);

        TiXmlElement* expenseIDElement_Expense = new TiXmlElement("TransactionID");
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
        IDofLastIncome++;
    }
}
