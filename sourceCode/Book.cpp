/* Citation and Sources...
Final Project Milestone 4
Module: Book
Filename: Book.cpp
Version 1.0
Author	Leo Ru 144337227 July 28,2023
Revision History
-----------------------------------------------------------
Date      Reason
2023/?/?  Preliminary release
2023/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <iostream>
#include <string.h>
#include <cstring>
#include <iomanip>
using namespace std;
namespace sdds {
	Book::Book() : Publication(){
		authorName = nullptr;
	}

	Book::~Book() {
		delete[] authorName;
		authorName = nullptr;
	}

	Book::Book(const Book& src):Publication(src) {
		if (authorName)
		{
			delete[] authorName;
			authorName = nullptr;
		}
		
		
			authorName = new char[strlen(src.authorName) + 1];
			strcpy(authorName, src.authorName);
		
		
	}

Book& Book::operator=(const Book& src) {
    Publication::operator=(src);
    if (this != &src)
    {
        if (authorName)
        {
            delete[] authorName;
            authorName = nullptr;
        }
        if (src.authorName)
        {
            authorName = new char[strlen(src.authorName) + 1];
            strcpy(authorName, src.authorName);
        }

    }
    return *this;
}

	char Book::type()const {
		return 'B';
	}

	Book::operator bool() const {
		
		bool ret = false;
		if (authorName)
		{
			if (Publication::operator bool())
			{
				ret = true;
			}
		}
		return ret;
	}
	
	void Book::set(int member_id) {
		Publication::set(member_id);
		Publication::resetDate();
	}


	std::ostream& Book::write(std::ostream& os) const {
		Publication::write(os);
		if (conIO(os))
		{
			os << " ";
			if (conIO(os)) {
				char author[SDDS_AUTHOR_WIDTH + 1] = { 0 };
				std::strncpy(author, authorName, SDDS_AUTHOR_WIDTH);
				os << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ') << author << " |";
			}
			
		}
		else
		{
			os << "\t" << authorName;
		}
		return os;
	}

	std::istream& Book::read(std::istream& istr) {
		char name[256] = { 0 };
		Publication::read(istr);
		if (authorName)
		{
			delete[] authorName;
			authorName = nullptr;
		}
		if (conIO(istr))
		{
			istr.ignore();
			cout << "Author: ";
			
		}
		else
		{
			istr.ignore(1000,'\t');
			
		}
		istr.get(name, 256);
		if (istr) {
			authorName = new char[strlen(name) + 1];
			strcpy(authorName, name);
		}
		return istr;
	}
}