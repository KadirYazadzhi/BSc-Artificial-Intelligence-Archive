

#include <iostream>  
#include <limits>    
#include <iomanip>   
#include <cstdlib>   

#include "menu.h"    
#include "utils.h"   
#include "add.h"     
#include "display.h" 
#include "delete.h"  
#include "file.h"    
#include "reports.h" 
#include "search.h"  
#include "sort.h"    
#include "update.h"  
#include "colors.h"  
#include "localization.h" 

using namespace std;


void mainMenu(Property properties[], int& propertyCount) {
  while (true) {
    clearConsole(); 
    cout << CYAN << getTranslatedString("MAIN_MENU_TITLE") << RESET << endl;
    cout << getTranslatedString("MAIN_MENU_ADD_PROPERTY") << endl;
    cout << getTranslatedString("MAIN_MENU_DELETE_PROPERTY") << endl;
    cout << getTranslatedString("MAIN_MENU_DISPLAY_PROPERTIES") << endl;
    cout << getTranslatedString("MAIN_MENU_SEARCH") << endl;
    cout << getTranslatedString("MAIN_MENU_SORT") << endl;
    cout << getTranslatedString("MAIN_MENU_FILE_OPERATIONS") << endl;
    cout << getTranslatedString("MAIN_MENU_UPDATE_DATA") << endl;
    cout << getTranslatedString("MAIN_MENU_REPORTS") << endl;
    cout << getTranslatedString("MAIN_MENU_EXIT") << endl;
    
    
    int choice = getMenuChoice(0, 8);

    switch (choice) {
      case 0:
        
        saveToSyncTextFile(properties, propertyCount); 
        cout << YELLOW << getTranslatedString("THANK_YOU_MESSAGE") << RESET << endl;
        exit(0); 
      case 1: addPropertyMenu(properties, propertyCount); break;      
      case 2: deletePropertyMenu(properties, propertyCount); break;   
      case 3: displayMenu(properties, propertyCount); break;          
      case 4: searchMenu(properties, propertyCount); break;           
      case 5: sortMenu(properties, propertyCount); break;             
      case 6: fileMenu(properties, propertyCount); break;             
      case 7: updateProperty(properties, propertyCount); break;       
      case 8: reportsMenu(properties, propertyCount); break;          
      default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; 
    }
  }
}


void addPropertyMenu(Property properties[], int& propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("ADD_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("ADD_MENU_SINGLE_PROPERTY") << endl;
  cout << getTranslatedString("ADD_MENU_MULTIPLE_PROPERTIES") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; 

  
  int choice = getMenuChoice(0, 2);

  switch (choice) {
    case 0: return; 
    case 1: addSingleProperty(properties, propertyCount); break;   
    case 2: addMultipleProperties(properties, propertyCount); break; 
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; 
  }
}


void deletePropertyMenu(Property properties[], int& propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("DELETE_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("DELETE_MENU_SINGLE_PROPERTY") << endl;
  cout << getTranslatedString("DELETE_MENU_ALL_PROPERTIES") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; 

  
  int choice = getMenuChoice(0, 2);

  switch (choice) {
    case 0: return; 
    case 1: DeleteProperty(properties, propertyCount); break;   
    case 2: DeleteAllProperties(properties, propertyCount); break; 
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; 
  }
}


void displayMenu(const Property properties[], int propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("DISPLAY_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("DISPLAY_MENU_ALL_PROPERTIES") << endl;
  cout << getTranslatedString("DISPLAY_MENU_SOLD_PROPERTIES") << endl;
  cout << getTranslatedString("DISPLAY_MENU_LARGEST_PROPERTIES") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; 

  
  int choice = getMenuChoice(0, 3);

  switch (choice) {
    case 0: return; 
    case 1: displayAllProperties(properties, propertyCount); break;   
    case 2: displaySoldProperties(properties, propertyCount); break; 
    case 3: displayLargestProperties(properties, propertyCount); break; 
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; 
  }
}


void searchMenu(Property properties[], int propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("SEARCH_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("SEARCH_MENU_BY_BROKER") << endl;
  cout << getTranslatedString("SEARCH_MENU_BY_ROOMS") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; 

  
  int choice = getMenuChoice(0, 2);

  switch (choice) {
    case 0: return; 
    case 1: searchByBroker(properties, propertyCount); break;   
    case 2: searchByRooms(properties, propertyCount); break;    
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; 
  }
}


void sortMenu(Property properties[], int propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("SORT_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("SORT_MENU_BROKER_PRICE") << endl;
  cout << getTranslatedString("SORT_MENU_ROOMS_PRICE") << endl;
  cout << getTranslatedString("SORT_MENU_ALL_PRICE_ASC") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; 

  
  int choice = getMenuChoice(0, 3);

  switch (choice) {
    case 0: return; 
    
    
    case 1: searchByBroker(properties, propertyCount); break; 
    case 2: searchByRooms(properties, propertyCount); break; 
    case 3:
        
        sortPropertiesArray(properties, propertyCount, true);
        syncDataToRecoveryFiles(properties, propertyCount); 
        cout << GREEN << getTranslatedString("SORT_ALL_PROPERTIES_SUCCESS") << RESET << endl;
        break;
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; 
  }
}


void fileMenu(Property properties[], int& propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("FILE_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("FILE_MENU_SAVE_BINARY") << endl;
  cout << getTranslatedString("FILE_MENU_LOAD_BINARY") << endl;
  cout << getTranslatedString("FILE_MENU_SAVE_TEXT") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; 

  
  int choice = getMenuChoice(0, 3);

  switch (choice) {
    case 0: return; 
    case 1: saveToBinaryFile(properties, propertyCount); break;           
    case 2: loadFromBinaryFile(properties, propertyCount); break;         
    case 3: saveToUserFriendlyTextFile(properties, propertyCount); break; 
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; 
  }
}


void reportsMenu(const Property properties[], int propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("REPORTS_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("REPORTS_MENU_MOST_EXPENSIVE_IN_AREA") << endl;
  cout << getTranslatedString("REPORTS_MENU_AVERAGE_PRICE_IN_AREA") << endl;
  cout << getTranslatedString("REPORTS_MENU_SOLD_PERCENTAGE_PER_BROKER") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; 

  
  int choice = getMenuChoice(0, 3);

  switch (choice) {
    case 0: return; 
    case 1: mostExpensiveInArea(properties, propertyCount); break;         
    case 2: averagePriceInArea(properties, propertyCount); break;           
    case 3: soldPercentagePerBroker(properties, propertyCount); break;     
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; 
  }
}