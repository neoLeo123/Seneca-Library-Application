/* Citation and Sources...
Final Project Milestone 3
Module: Streamable
Filename: Streamable.cpp
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

#include "Streamable.h"

namespace sdds {
	Streamable::~Streamable() {};



	std::ostream& operator<<(std::ostream& os, const Streamable& stream) {
		if (stream)
		{
			stream.write(os);
		}
		return os;
	}
	std::istream& operator>>(std::istream& is, Streamable& stream) {
		return (stream.read(is));
	}
}
