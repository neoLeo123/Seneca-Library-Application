/* Citation and Sources...
Final Project Milestone 4
Module: Publication
Filename: Publication.cpp
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
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string.h>
using namespace std;
namespace sdds {
	void Publication::setDefaultValue() {
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		resetDate();
	}

	Publication::Publication() {
		setDefaultValue();
	}

	void Publication::set(int member_id) {
		m_membership = member_id;
	}
	void Publication::setRef(int value) {
		m_libRef = value;
	}
	
	void Publication::resetDate() {
		m_date = Date();
	}
	char Publication::type()const {
		return 'P';
	}
	bool Publication::onLoan()const {
		return (m_membership != 0);
	}
	Date Publication::checkoutDate()const {
		return m_date;
	}

	bool Publication::operator==(const char* title)const {
		bool ret = false;
		char* pch = strstr(m_title, title);
		if (pch != nullptr)
		{
			ret = true;
		}
		return ret;
	}

	Publication::operator const char* ()const {
		return m_title;
	}
	int Publication::getRef()const {
		return m_libRef;
	}

	bool Publication::conIO(std::ios& io)const {
		return &io == &std::cin || &io == &std::cout;
	}

	std::ostream& Publication::write(std::ostream& os) const {
		char title[SDDS_TITLE_WIDTH + 1] = { 0 };
		strncpy(title, m_title, SDDS_TITLE_WIDTH);
		if (conIO(os))
		{
			os << "| " << m_shelfId << " | " << setw(30) << left << setfill('.') << title << " | ";
			(m_membership != 0) ? os << m_membership : os << " N/A ";
			os << " | " << m_date << " |";
		}
		else {
			os << type();
			os << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
			(m_membership != 0) ? os << m_membership : os << 0;
			os << "\t" << m_date;
		}
		return os;
	}

	std::istream& Publication::read(std::istream& istr) {

		char temptitle[256]{};
		char tempshelfId[SDDS_SHELF_ID_LEN + 1]{};
		int templibRef = -1;
		int tempmembership = 0;
		Date tempdate;
		if (m_title)
		{
			delete[] m_title;
			m_title = nullptr;
		}
		setDefaultValue();
		if (conIO(istr))
		{
			cout << "Shelf No: ";
			istr.getline(tempshelfId, SDDS_SHELF_ID_LEN + 1);
			if (strlen(tempshelfId) != SDDS_SHELF_ID_LEN) {
				istr.setstate(ios::failbit);
			}
			cout << "Title: ";
			istr.getline(temptitle, 256);

			cout << "Date: ";
			istr >> tempdate;
		}
		else
		{
			istr >> templibRef;
			istr.ignore();
			istr.getline(tempshelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			istr.getline(temptitle, 256, '\t');
			istr >> tempmembership;
			istr.ignore();
			istr >> tempdate;
		}
		if (!tempdate) {
			istr.setstate(ios::failbit);
		}
		if (istr) {
			m_title = new char[strlen(temptitle) + 1];
			strcpy(m_title, temptitle);
			strcpy(m_shelfId, tempshelfId);
			m_membership = tempmembership;
			m_date = tempdate;
			m_libRef = templibRef;
		}
		return istr;

	}
	
	Publication::operator bool() const {
		bool ret = false;
		if (m_title != nullptr && m_shelfId[0] != '\0') {
			ret = true;
		}
		return ret;
	}
	Publication::~Publication() {
		delete[] m_title;
		m_title = nullptr;
	}

	Publication::Publication(const Publication& publication) {
		*this = publication;
	}


	Publication& Publication::operator=(const Publication& publication) {
		if (this != &publication)
		{
			set(publication.m_membership);
			setRef(publication.m_libRef);
			strcpy(m_shelfId, publication.m_shelfId);
			m_date = publication.m_date;
			if (m_title)
			{
				delete[] m_title;
				m_title = nullptr;
			}
			if (publication.m_title != nullptr) {
				m_title = new char[strlen(publication.m_title) + 1];
				strcpy(m_title, publication.m_title);
			}
			else {
				m_title = nullptr;
			}
		}

		return *this;
	}
}




