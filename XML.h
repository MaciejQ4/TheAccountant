#pragma once

#include "User.h"
#include "tinystr.h"
#include "tinyxml.h"

class XML
{
private:

	const string NAME_OF_XML;

public:
	
	XML(string nameOfXML) :
		NAME_OF_XML(nameOfXML) {};
	
	string getFileName();
	//bool isFileEmpty();
};

