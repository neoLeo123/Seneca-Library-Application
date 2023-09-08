/* Citation and Sources...
Final Project Milestone 4
Module: Book
Filename: Book.h
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
#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include "Publication.h"
namespace sdds {
	class Book : public Publication {
		char* authorName;
		public:	
			Book();
			~Book();
			Book(const Book& src);
			Book& operator=(const Book& src);
			char type()const;
			std::ostream& write(std::ostream& os) const;
			std::istream& read(std::istream& istr);
			operator bool() const;
			virtual void set(int member_id);
			
	};
}
#endif


