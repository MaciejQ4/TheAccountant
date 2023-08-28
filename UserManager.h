#pragma once

#include "User.h"
#include "XML.h"

class UserManager
{
private:

	int loggedID = 0;
	vector <User> users;
	XML xml;

	User gatherCredentialsOfNewUser();
	int assignIDtoNewUser();
	bool doesLoginExist(string login);

public:

	UserManager(string nameOfUserXML) :
		xml(nameOfUserXML)
	{
		users = xml.uploadUsersFromXML();
	};
	
	int getLoggedID();
	void setLoggedID(int id);
	bool isUserLogged();
	
	void loginUser();
	void createUser();
	void showAllUsers();

	void changePassword();
	void logOut();
};
