/**
 * @file menu.cpp
 * @brief Implementation of the application menu system and user interaction flow.
 *
 * This file contains the concrete implementations for various menus, including
 * the main menu and sub-menus for adding, deleting, displaying, searching,
 * sorting, file operations, and reports. These functions guide the user
 * through the application's features, handle menu selections, and
 * delegate tasks to appropriate modules.
 */

#include <iostream>  // Necessary for standard I/O operations (cout, cin)
#include <limits>    // Necessary for numeric_limits (used in cin.ignore)
#include <iomanip>   // Necessary for output formatting (setw)
#include <cstdlib>   // Necessary for exit()

#include "menu.h"    // Header with menu function declarations
#include "utils.h"   // Helper functions like clearConsole, getMenuChoice
#include "add.h"     // Functions for adding properties
#include "display.h" // Functions for displaying properties
#include "delete.h"  // Functions for deleting properties
#include "file.h"    // Functions for file operations (save/load)
#include "reports.h" // Functions for generating reports
#include "search.h"  // Functions for searching properties
#include "sort.h"    // Functions for sorting properties
#include "update.h"  // Functions for editing/updating properties
#include "colors.h"  // Defines ANSI escape codes for console coloring
#include "localization.h" // Localization functions like getTranslatedString

using namespace std;

/**
 * @brief Displays the main application menu and handles top-level user choices.
 *
 * This function loops continuously, displaying the main menu options to the user
 * and prompting for a choice. It uses `getMenuChoice` to validate input and then
 * calls the appropriate sub-menu or function based on the user's selection.
 * The loop only breaks when the user chooses to exit the application.
 * Before exiting, it ensures current data is saved for recovery.
 *
 * @param properties Array of `Property` structures representing the main dataset.
 * @param propertyCount Reference to an integer containing the current number of properties.
 */
void mainMenu(Property properties[], int& propertyCount) {
  while (true) {
    clearConsole(); // Clear console for clean menu display.
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
    
    // Get and validate user's menu choice (options 0 to 8).
    int choice = getMenuChoice(0, 8);

    switch (choice) {
      case 0:
        // Exit option: save recovery data and display goodbye message.
        saveToSyncTextFile(properties, propertyCount); // Save current state for recovery.
        cout << YELLOW << getTranslatedString("THANK_YOU_MESSAGE") << RESET << endl;
        exit(0); // Terminate the program.
      case 1: addPropertyMenu(properties, propertyCount); break;      // Go to Add Property menu.
      case 2: deletePropertyMenu(properties, propertyCount); break;   // Go to Delete Property menu.
      case 3: displayMenu(properties, propertyCount); break;          // Go to Display Properties menu.
      case 4: searchMenu(properties, propertyCount); break;           // Go to Search menu.
      case 5: sortMenu(properties, propertyCount); break;             // Go to Sort menu.
      case 6: fileMenu(properties, propertyCount); break;             // Go to File Operations menu.
      case 7: updateProperty(properties, propertyCount); break;       // Call Update Property function directly.
      case 8: reportsMenu(properties, propertyCount); break;          // Go to Reports menu.
      default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; // Handle invalid input.
    }
  }
}

/**
 * @brief Displays the property addition menu and handles user choices.
 *
 * This sub-menu provides options to add a single property or multiple properties.
 * Clears the console, displays localized options, and then calls the
 * appropriate function (`addSingleProperty` or `addMultipleProperties`)
 * based on the user's validated choice.
 *
 * @param properties Array of `Property` structures where new properties will be added.
 * @param propertyCount Reference to an integer containing the current number of properties.
 */
void addPropertyMenu(Property properties[], int& propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("ADD_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("ADD_MENU_SINGLE_PROPERTY") << endl;
  cout << getTranslatedString("ADD_MENU_MULTIPLE_PROPERTIES") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; // Option to return to main menu.

  // Get and validate user's menu choice (options 0 to 2).
  int choice = getMenuChoice(0, 2);

  switch (choice) {
    case 0: return; // Return to the calling menu (main menu).
    case 1: addSingleProperty(properties, propertyCount); break;   // Add a single property.
    case 2: addMultipleProperties(properties, propertyCount); break; // Add multiple properties.
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; // Handle invalid input.
  }
}

/**
 * @brief Displays the property deletion menu and handles user choices.
 *
 * This sub-menu offers options to delete a single property by reference number
 * or to clear all properties from the system. Uses `getMenuChoice` to
 * validate input and calls the corresponding deletion function.
 *
 * @param properties Array of `Property` structures from which properties will be deleted.
 * @param propertyCount Reference to an integer containing the current number of properties.
 */
void deletePropertyMenu(Property properties[], int& propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("DELETE_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("DELETE_MENU_SINGLE_PROPERTY") << endl;
  cout << getTranslatedString("DELETE_MENU_ALL_PROPERTIES") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; // Reusing "0. Назад" for consistency.

  // Get and validate user's menu choice (options 0 to 2).
  int choice = getMenuChoice(0, 2);

  switch (choice) {
    case 0: return; // Return to the calling menu.
    case 1: DeleteProperty(properties, propertyCount); break;   // Delete a single property.
    case 2: DeleteAllProperties(properties, propertyCount); break; // Delete all properties.
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; // Handle invalid input.
  }
}

/**
 * @brief Displays the property viewing menu and handles user choices.
 *
 * This sub-menu presents options to display all properties, only sold properties,
 * or properties with the largest total area. Calls the appropriate display function
 * based on the user's validated input.
 *
 * @param properties Constant array of `Property` structures to display.
 * @param propertyCount The current number of properties in the system.
 */
void displayMenu(const Property properties[], int propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("DISPLAY_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("DISPLAY_MENU_ALL_PROPERTIES") << endl;
  cout << getTranslatedString("DISPLAY_MENU_SOLD_PROPERTIES") << endl;
  cout << getTranslatedString("DISPLAY_MENU_LARGEST_PROPERTIES") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; // Reusing "0. Back" for consistency.

  // Get and validate user's menu choice (options 0 to 3).
  int choice = getMenuChoice(0, 3);

  switch (choice) {
    case 0: return; // Return to the calling menu.
    case 1: displayAllProperties(properties, propertyCount); break;   // Display all properties.
    case 2: displaySoldProperties(properties, propertyCount); break; // Display only sold properties.
    case 3: displayLargestProperties(properties, propertyCount); break; // Display largest properties.
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; // Handle invalid input.
  }
}

/**
 * @brief Displays the property search menu and handles user choices.
 *
 * This sub-menu allows users to search properties by broker name or
 * by number of rooms. Calls the relevant search function based
 * on the user's validated choice.
 *
 * @param properties Constant array of `Property` structures to search.
 * @param propertyCount The current number of properties in the system.
 */
void searchMenu(Property properties[], int propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("SEARCH_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("SEARCH_MENU_BY_BROKER") << endl;
  cout << getTranslatedString("SEARCH_MENU_BY_ROOMS") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; // Reusing "0. Back" for consistency.

  // Get and validate user's menu choice (options 0 to 2).
  int choice = getMenuChoice(0, 2);

  switch (choice) {
    case 0: return; // Return to the calling menu.
    case 1: searchByBroker(properties, propertyCount); break;   // Search by broker name.
    case 2: searchByRooms(properties, propertyCount); break;    // Search by room count.
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; // Handle invalid input.
  }
}

/**
 * @brief Displays the property sorting menu and handles user choices.
 *
 * This sub-menu provides options to sort properties based on different criteria.
 * The current implementation allows sorting by price for specific search results
 * or sorting the entire property array by price in ascending order.
 *
 * @param properties Array of `Property` structures to sort.
 * @param propertyCount The current number of properties in the system.
 */
void sortMenu(Property properties[], int propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("SORT_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("SORT_MENU_BROKER_PRICE") << endl;
  cout << getTranslatedString("SORT_MENU_ROOMS_PRICE") << endl;
  cout << getTranslatedString("SORT_MENU_ALL_PRICE_ASC") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; // Reusing "0. Back" for consistency.

  // Get and validate user's menu choice (options 0 to 3).
  int choice = getMenuChoice(0, 3);

  switch (choice) {
    case 0: return; // Return to the calling menu.
    // Note: Cases 1 and 2 here currently reimplement search functionality,
    // which might be better handled in the search menu or by passing sort preferences to search.
    case 1: searchByBroker(properties, propertyCount); break; 
    case 2: searchByRooms(properties, propertyCount); break; 
    case 3:
        // Sort the entire property array by price in ascending order.
        sortPropertiesArray(properties, propertyCount, true);
        syncDataToRecoveryFiles(properties, propertyCount); // Synchronize after sorting.
        cout << GREEN << getTranslatedString("SORT_ALL_PROPERTIES_SUCCESS") << RESET << endl;
        break;
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; // Handle invalid input.
  }
}

/**
 * @brief Displays the file operations menu (save/load) and handles user choices.
 *
 * This sub-menu provides options to save property data to a binary file,
 * load data from a binary file, or save data to a user-friendly text report.
 * Calls the appropriate file handling function based on the user's validated input.
 *
 * @param properties Array of `Property` structures for file operations.
 * @param propertyCount Reference to an integer containing the current number of properties.
 */
void fileMenu(Property properties[], int& propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("FILE_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("FILE_MENU_SAVE_BINARY") << endl;
  cout << getTranslatedString("FILE_MENU_LOAD_BINARY") << endl;
  cout << getTranslatedString("FILE_MENU_SAVE_TEXT") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; // Reusing "0. Back" for consistency.

  // Get and validate user's menu choice (options 0 to 3).
  int choice = getMenuChoice(0, 3);

  switch (choice) {
    case 0: return; // Return to the calling menu.
    case 1: saveToBinaryFile(properties, propertyCount); break;           // Save data to binary file.
    case 2: loadFromBinaryFile(properties, propertyCount); break;         // Load data from binary file.
    case 3: saveToUserFriendlyTextFile(properties, propertyCount); break; // Save data to user-friendly text file.
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; // Handle invalid input.
  }
}

/**
 * @brief Displays the report generation menu and handles user choices.
 *
 * This sub-menu offers options to generate various analytical reports,
 * such as finding the most expensive property in an area, calculating
 * the average price in an area, or determining sold percentages per broker.
 * Calls the relevant report generation function.
 *
 * @param properties Constant array of `Property` structures for report generation.
 * @param propertyCount The current number of properties in the system.
 */
void reportsMenu(const Property properties[], int propertyCount) {
  clearConsole();
  cout << CYAN << getTranslatedString("REPORTS_MENU_TITLE") << RESET << endl;
  cout << getTranslatedString("REPORTS_MENU_MOST_EXPENSIVE_IN_AREA") << endl;
  cout << getTranslatedString("REPORTS_MENU_AVERAGE_PRICE_IN_AREA") << endl;
  cout << getTranslatedString("REPORTS_MENU_SOLD_PERCENTAGE_PER_BROKER") << endl;
  cout << getTranslatedString("ADD_MENU_BACK") << endl; // Reusing "0. Back" for consistency.

  // Get and validate user's menu choice (options 0 to 3).
  int choice = getMenuChoice(0, 3);

  switch (choice) {
    case 0: return; // Return to the calling menu.
    case 1: mostExpensiveInArea(properties, propertyCount); break;         // Generate most expensive in area report.
    case 2: averagePriceInArea(properties, propertyCount); break;           // Generate average price in area report.
    case 3: soldPercentagePerBroker(properties, propertyCount); break;     // Generate sold percentage per broker report.
    default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break; // Handle invalid input.
  }
}