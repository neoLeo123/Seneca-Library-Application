/* Citation and Sources...
Final Project Milestone 3
Module: LibApp
Filename: LibApp.h
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
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
namespace sdds {
   class LibApp {
       bool m_changed;
       char fileName[256+1];
       Publication* records[SDDS_LIBRARY_CAPACITY];
       int numPublications;
       int lastLRN;
       
       Menu m_mainMenu;
       Menu m_exitMenu;
       Menu publicationType;
       bool confirm(const char* message);
       void load();  // prints: "Loading Data"<NEWLINE>
       void save();  // prints: "Saving Data"<NEWLINE>
       int search(int type);  // prints: "Searching for publication"<NEWLINE>

       void returnPub();  /*  Calls the search() method.
                              prints "Returning publication"<NEWLINE>
                              prints "Publication returned"<NEWLINE>
                              sets m_changed to true;
                          */
     
       void newPublication();
       void removePublication();
       void checkOutPub();
      
   public:
       LibApp(const char* filename);
       void run();
       ~LibApp();
       Publication* getPub(int libRef);
   };
}
#endif // !SDDS_LIBAPP_H

