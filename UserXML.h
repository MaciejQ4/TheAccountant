#pragma once

#include "XML.h"

class UserXML : protected XML
{
public:

	UserXML(string NAME_OF_USER_XML) : XML(NAME_OF_USER_XML) {};

	vector<User> uploadUsersFromXML();
	void appendUserToXML(User user);
	void replaceChangedPasswordInXMLfile(int LOGGED_ID, string newPassword, User user);

};

