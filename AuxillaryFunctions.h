#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class AuxillaryFunctions
{
public:

	static string readLine();
	static char readChar();
	static string addDashToDate(int date);
	static int eraseDashFromDate(string date);
};

