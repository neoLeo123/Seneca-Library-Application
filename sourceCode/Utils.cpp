/* Citation and Sources...
Final Project Milestone 3
Module: Utils
Filename: Utils.cpp
Version 1.0
Author	Leo Ru 144337227 July 20,2023
Revision History
-----------------------------------------------------------
Date      Reason
2023/?/?  Preliminary release
2023/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include "Utils.h"
using namespace std;
namespace sdds {
	int getInteger(int min, int max, const char* message) {
		int input, flag = 0;
		do
		{
			cin >> input;
			if (!cin || input < min || input > max)
			{
				cout << message;
				cin.clear();
				cin.ignore(2000, '\n');
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);
		return input;
	}
	int getInteger(int min, int max) {
		int input, flag = 0;
		do
		{
			cin >> input;
			if (!cin || input < min || input > max)
			{
				
				cin.clear();
				cin.ignore(2000, '\n');
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);
		return input;
	}
}