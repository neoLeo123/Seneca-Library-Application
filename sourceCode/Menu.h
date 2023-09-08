// Final Project Milestone 1 
// Date Module
// File	Date.h
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
// 
/////////////////////////////////////////////////////////////////
/*Leo Ru
lru1@myseneca.ca
144337227
July 11,2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.*/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
#define MAX_MENU_ITEMS 20
namespace sdds {
	class Menu;

	class MenuItem {
		char* itemName;
		friend class Menu;
		MenuItem();
		MenuItem(const char* src);
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem& src) = delete;
		void setEmpty();
		~MenuItem();
		operator bool() const;
		operator const char* () const;
		std::ostream& display(std::ostream& os = std::cout)const;
	};

	class Menu {
		MenuItem menuTitle{};
		MenuItem* menuItems[MAX_MENU_ITEMS]{};
		unsigned int pointerNum = 0;
	public:
		Menu();
		Menu(const char* title);
		~Menu();
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu& src) = delete;
		std::ostream& displayMenuTitle(std::ostream& os = std::cout);
		std::ostream& displayMenu(std::ostream& os = std::cout);
		int run();
		int operator~();
		Menu& operator<<(const char* menuitemContent);
		operator int();
		operator unsigned int();
		operator bool();
		const char* operator[](unsigned int index) const;
		
	};
	std::ostream& operator<<(std::ostream& os, Menu& menu);
}
#endif