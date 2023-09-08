// Final Project Milestone 1 
// Date Module
// File	Date.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
/*Leo Ru
lru1@myseneca.ca
144337227
July 11,2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Utils.h"
#include <string.h>
using namespace std;
#include "Menu.h"
namespace sdds {
	
	void MenuItem::setEmpty() {
		itemName = nullptr;
	}
	MenuItem::MenuItem() {
		setEmpty();
	}
	MenuItem::MenuItem(const char* src) {
		if (src != nullptr && src[0] != '\0')
		{
			itemName = new char[strlen(src) + 1];
			strcpy(itemName, src);
		}
		else
		{
			setEmpty();
		}
	}
	MenuItem::~MenuItem() {
		delete[] itemName;
		itemName = nullptr;
	}
	MenuItem::operator bool() const {

		return (itemName && itemName[0]);
	}

	MenuItem::operator const char* () const {
		return itemName;
	}
	std::ostream& MenuItem::display(std::ostream& os)const {

		if (*this)
		{
			os << itemName;
		}return os;
	}
	Menu::Menu() {
		pointerNum = 0;

	}
	Menu::Menu(const char* title) : menuTitle(title) {};

	Menu::~Menu() {
		unsigned int i;
		for (i = 0; i < MAX_MENU_ITEMS; i++)
		{
			delete menuItems[i];
		}
	}

	std::ostream& Menu::displayMenuTitle(std::ostream& os) {

		if (menuTitle)
		{
			menuTitle.display();
		}
		return os;
	}
	std::ostream& Menu::displayMenu(std::ostream& os) {

		if (menuTitle)
		{
			displayMenuTitle();
			os << endl;
		}

		for (unsigned int i = 0; i < MAX_MENU_ITEMS && menuItems[i] != nullptr; i++)
		{
			os << setw(2) << right << setfill(' ');
			os << i + 1 << "- ";
			os << left << setw(0);
			menuItems[i]->display(os);
			os << endl;

		}
		os << " 0- Exit" << std::endl;
		os << "> ";
		return os;
	}
	int Menu::run() {
		int input;
		displayMenu();
		input = getInteger(0, pointerNum);
		return input;
	}

	int Menu::operator~() {
		return run();
	}
	Menu& Menu::operator<<(const char* menuitemContent) {
		if (pointerNum < MAX_MENU_ITEMS)
		{
			MenuItem* newItem = new MenuItem(menuitemContent);
			menuItems[pointerNum] = newItem;
			pointerNum++;
		}
		return *this;
	}
	Menu::operator int() {
		return pointerNum;

	}
	Menu::operator unsigned int() {
		return pointerNum;
	}
	Menu::operator bool() {
		bool ret = false;
		if (pointerNum > 0)
		{
			ret = true;
		}
		return ret;
	}
	std::ostream& operator<<(std::ostream& os, Menu& menu) {
		return (menu.displayMenuTitle(os));

	}

	const char* Menu::operator[](unsigned int index) const {
		if (index > pointerNum)
		{
			return menuItems[index %= pointerNum]->itemName;
		}
		else
		{
			return menuItems[index]->itemName;
		}
	}
}
