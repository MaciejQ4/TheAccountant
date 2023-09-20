#pragma once

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class AuxillaryFunctions
{
public:

	static string readLine();
	static char readChar();

	static string addDashesToDate(int date);
	static int eraseDashesFromDate(string date);

	static bool isLeapYear(int year);
	static int getTodaysDate();
	static int elapsedDaysThisMonth();
	
	static bool checkDateFormat(string userInputDate);
	static bool checkAmountFormat(string userInputAmount);
};

