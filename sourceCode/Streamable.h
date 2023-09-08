
/* Citation and Sources...
Final Project Milestone 3
Module: Streamable
Filename: Streamable.h
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
#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H

#include <iostream>

namespace sdds
{
	class Streamable {
	public:
		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream& is) = 0;

		virtual bool conIO(std::ios& io) const = 0;

		virtual operator bool() const = 0;
		virtual ~Streamable();


	};
	std::ostream& operator<<(std::ostream& os, const Streamable& stream);
	std::istream& operator>>(std::istream& is, Streamable& stream);
}

#endif
