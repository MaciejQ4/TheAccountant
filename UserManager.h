#pragma once

#include "User.h"
#include "XML.h"
#include "UserXML.h"

class UserManager
{
private:

	int loggedID = 0;
	vector <User> users;
	UserXML userXML;

	User gatherCredentialsOfNewUser();
	int assignIDtoNewUser();
	bool doesLoginExist(string login);

public:

	UserManager(string NAME_OF_USER_XML) :
		userXML(NAME_OF_USER_XML)
	{
		users = userXML.uploadUsersFromXML();
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
