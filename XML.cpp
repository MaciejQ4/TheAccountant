#include "XML.h"

vector<User> XML::uploadUsersFromXML() {

    vector<User> users;
    TiXmlDocument doc;

    if (doc.LoadFile(NAME_OF_USER_XML.c_str())) {
        TiXmlElement* root = doc.RootElement();
        if (!root) {
            std::cout << "Error: Root element not found in XML." << std::endl;
            return users;
        }

        for (TiXmlElement* userElement = root->FirstChildElement("User"); userElement; userElement = userElement->NextSiblingElement("User")) {
            int userID = 0;
            std::string userLogin, userPassword;

            TiXmlElement* userIDElement = userElement->FirstChildElement("UserID");
            if (userIDElement) {
                const char* idText = userIDElement->GetText();
                if (idText)
                    userID = std::stoi(idText);
            }

            TiXmlElement* userLoginElement = userElement->FirstChildElement("UserLogin");
            if (userLoginElement) {
                const char* loginText = userLoginElement->GetText();
                if (loginText)
                    userLogin = loginText;
            }

            TiXmlElement* userPasswordElement = userElement->FirstChildElement("UserPassword");
            if (userPasswordElement) {
                const char* passwordText = userPasswordElement->GetText();
                if (passwordText)
                    userPassword = passwordText;
            }

            users.push_back(User(userID, userLogin, userPassword));
        }
    }
    else {
        std::cout << "Error loading XML file." << std::endl;
    }
    return users;
}

void XML::appendUserToXML(User user) {

        TiXmlDocument doc;

        if (doc.LoadFile(NAME_OF_USER_XML.c_str()))
        {
            TiXmlElement* root = doc.RootElement();

            TiXmlElement* userElement = new TiXmlElement("User");
            root->LinkEndChild(userElement);

            TiXmlElement* userIDElement = new TiXmlElement("UserID");
            userIDElement->LinkEndChild(new TiXmlText(std::to_string(user.getUserID()).c_str()));
            userElement->LinkEndChild(userIDElement);

            TiXmlElement* userLoginElement = new TiXmlElement("UserLogin");
            userLoginElement->LinkEndChild(new TiXmlText(user.getUserLogin().c_str()));
            userElement->LinkEndChild(userLoginElement);

            TiXmlElement* userPasswordElement = new TiXmlElement("UserPassword");
            userPasswordElement->LinkEndChild(new TiXmlText(user.getUserPassword().c_str())); 
            userElement->LinkEndChild(userPasswordElement);

            doc.SaveFile(NAME_OF_USER_XML.c_str());
        }
        else
        {
            TiXmlElement* root = new TiXmlElement("Users");
            doc.LinkEndChild(root);

            TiXmlElement* userElement = new TiXmlElement("User");
            root->LinkEndChild(userElement);

            TiXmlElement* userIDElement = new TiXmlElement("UserID");
            userIDElement->LinkEndChild(new TiXmlText(std::to_string(user.getUserID()).c_str()));
            userElement->LinkEndChild(userIDElement);

            TiXmlElement* userLoginElement = new TiXmlElement("UserLogin");
            userLoginElement->LinkEndChild(new TiXmlText(user.getUserLogin().c_str()));
            userElement->LinkEndChild(userLoginElement);

            TiXmlElement* userPasswordElement = new TiXmlElement("UserPassword");
            userPasswordElement->LinkEndChild(new TiXmlText(user.getUserPassword().c_str()));
            userElement->LinkEndChild(userPasswordElement);

            doc.SaveFile(NAME_OF_USER_XML.c_str());
        }
}

bool XML::isUserXMLEmpty() {
	cout << "is xml empty";
	return true;
}