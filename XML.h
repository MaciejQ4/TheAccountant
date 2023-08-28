#pragma once

#include "User.h"

#include "tinystr.h"
#include "tinyxml.h"

class XML
{
private:

	const string NAME_OF_USER_XML;

	bool isUserXMLEmpty();

public:
	
	XML(string nameOfUserXML) :
		NAME_OF_USER_XML(nameOfUserXML) {};
	
	vector<User> uploadUsersFromXML();
	void appendUserToXML(User user);
};

