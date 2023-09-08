/* Citation and Sources...
Final Project Milestone 3
Module: LibApp
Filename: LibApp.cpp
Version 1.0
Author	Leo Ru 144337227 August 3,2023
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

#include <iostream>
#include "LibApp.h"
#include "Menu.h"
#include "PublicationSelector.h"
#include <fstream>
#include <cstring>
#include "Publication.h"
#include "Utils.h"
#include "Book.h"
#include <iomanip>
using namespace std;
namespace sdds {
	
	LibApp::LibApp(const char* infilename) :m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), publicationType("Choose the type of publication:") {
		m_changed = false;
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		publicationType << "Book" << "Publication";
		numPublications = 0;
		lastLRN = 0;
		strcpy(fileName, infilename);
		fileName[256] = '\0';
		load();
	}

	bool LibApp::confirm(const char* message) {
		bool ret = false;
		Menu menu(message);
		menu << "Yes";
		int result = menu.run();
		if (result == 1)
		{
			ret = true;
		}
		return ret;
	}
	

	void LibApp::load() {
		cout << "Loading Data" << endl;
		ifstream inputfile(fileName);
		char typeofPub{};
		int i;
		
		for ( i = 0; i < SDDS_LIBRARY_CAPACITY && inputfile; i++)
		{
			inputfile >> typeofPub;
			inputfile.ignore();
			if (inputfile)
			{
				if (typeofPub == 'P')
				{
					records[i] = new Publication;
				}
				else if (typeofPub == 'B')
				{
					records[i] = new Book;
				}
				if (records[i])
				{
					inputfile >> *records[i];
					numPublications++;
					lastLRN = records[i]->getRef();
				}
			}
		}
		
	}
	

	void LibApp::save() {
		cout << "Saving Data" << endl;
		ofstream outputfile(fileName);
		for (int i = 0; i < numPublications; i++)
		{
			if (records[i]->getRef() !=0)
			{
				outputfile << *records[i] << endl;
			}
		}
		outputfile.close();
	}

	int LibApp::search(int type) {
		int userselected=0, libraryref=0;
		char title[256]{};
		char chartype;
		int i;
		PublicationSelector selectpub("Select one of the following found matches:", 15);

		userselected = publicationType.run();
		if (userselected == 1)
		{
			chartype = 'B';
		}
		else if (userselected == 2)
		{
			chartype = 'P';
		}
		cin.ignore(1000, '\n');
		cout << "Publication Title: ";
		cin.getline(title, 256);

		if (type == 1) {

			
			for (i = 0; i < numPublications; i++) {

				if (records[i]->operator==(title) && chartype == records[i]->type() && records[i]->getRef() != 0) {
					selectpub << records[i];
				}
			}
		}

		else if (type == 2) {

			for (i = 0; i < numPublications; i++) {

				if (records[i]->operator==(title) && records[i]->onLoan() && chartype == records[i]->type() && records[i]->getRef() != 0) {
					selectpub << records[i];
				}
			}
		}

		else if (type == 3) {

			for (i = 0; i < numPublications; i++) {

				if (records[i]->operator==(title) && !records[i]->onLoan() && chartype == records[i]->type() && records[i]->getRef() != 0) {
					selectpub << records[i];
				}
			}
		}

		if (selectpub) {
			selectpub.sort();
			libraryref = selectpub.run();

			if (libraryref > 0)
			{
				cout << *getPub(libraryref) << endl;
			}

			else {
				cout << "Aborted!" << endl;
			}
		}

		else {
			cout << "No matches found!" << endl;
		}

		return libraryref;
	}

	Publication* LibApp::getPub(int libRef) {
		Publication* ret = nullptr;
		for (int i = 0; i < numPublications; i++)
		{
			if (records[i]->getRef() == libRef)
			{
				ret = records[i];
			}
		}
		return ret;
	}
	void LibApp::returnPub() {
		bool aborted = false;		
		cout << "Return publication to the library" << endl;
		int referencenum = search(2);	
		if (referencenum <= 0) {
			aborted = true;
		}

		if (!aborted) {
			bool confirmed = confirm("Return Publication?");
			if (confirmed) {
				int overdays = Date() - getPub(referencenum)->checkoutDate();

				if (overdays > SDDS_MAX_LOAN_DAYS) {

					double penalty = (overdays - SDDS_MAX_LOAN_DAYS) * 0.5;
					cout << fixed << setprecision(2);
					cout << "Please pay $" << penalty << " penalty for being " << (overdays - SDDS_MAX_LOAN_DAYS) << " days late!" << std::endl;
				}
				getPub(referencenum)->set(0);
				m_changed = true;
			}
			cout << "Publication returned" << endl;
		}
		cout << endl;
	}
	void LibApp::newPublication() {
		bool aborted = false;

		if (numPublications == SDDS_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
			aborted = true;
		}

		if (!aborted) {
			cout << "Adding new publication to the library" << endl;

			int pubType = publicationType.run();
			cin.ignore(1000, '\n');

			Publication* p = nullptr;

			if (pubType == 0) {
				cout << "Aborted!" << endl;
				aborted = true;
			}
			else if (pubType == 1) {
				p = new Book;
				cin >> *p;
			}
			else if (pubType == 2) {
				p = new Publication;
				cin >> *p;
			}

			if (!cin.fail())
			{
				if (!aborted && confirm("Add this publication to the library?")) {

					if (!*p) {
						cout << "Failed to add publication!" << endl;
						delete p;
					}

					else {

						lastLRN++;
						p->setRef(lastLRN);

						records[numPublications] = p;

						numPublications++;
						m_changed = true;

						cout << "Publication added" << endl;
					}
				}
			}
			else {
				cin.ignore(1000, '\n');
				cin.clear();
				cout << "Aborted!" << endl;
			}
		}
		cout << endl;
	}

	


	void LibApp::removePublication() {
		
		cout << "Removing publication from the library" << endl;
		int referencenum=search(1);
		if (referencenum) {
			if (confirm("Remove this publication from the library?"))
			{
				getPub(referencenum)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
		cout << endl;
	}

	void LibApp::checkOutPub() {
		cout << "Checkout publication from the library" << endl;
		int referencenum = search(3);
		if (referencenum > 0) {
			bool confirmed = confirm("Check out publication?");
			if (confirmed) {
				cout << "Enter Membership number: ";
				int inputMembership = getInteger(10000, 99999, "Invalid membership number, try again: ");
				getPub(referencenum)->set(inputMembership);

				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
		cout << endl;
	}

	
	void LibApp::run() {
		int userSelection = 1; 
		int userExit;

		while (userSelection != 0) {
			userSelection = m_mainMenu.run();

			if (userSelection == 0) {
				if (m_changed) {
					userExit = m_exitMenu.run();

					if (userExit == 0) {
						if (confirm("This will discard all the changes are you sure?")) {
							m_changed = false;
						}
					}
					else if (userExit == 1) {
						save();
					}
					else if (userExit == 2) {
						userSelection = 1;
					}
				}
				cout << endl;
			}
			else if (userSelection == 1) {
				newPublication();
			}
			else if (userSelection == 2) {
				removePublication();
			}
			else if (userSelection == 3) {
				checkOutPub();
			}
			else if (userSelection == 4) {
				returnPub();
			}
		}

		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}

	LibApp::~LibApp() {
		for (int i = 0; i < numPublications; i++)
		{
			delete records[i];
			records[i] = nullptr;
		}
	}

}

