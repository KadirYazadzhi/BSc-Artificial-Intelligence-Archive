/**
 * @file main.cpp
 * @brief Main entry point for the Real Estate Agency Management System application.
 *
 * This file contains the `main` function, which initializes the application,
 * loads initial data, handles language selection, displays the application banner,
 * and then enters the main menu loop. It orchestrates the overall program flow.
 */

#include "structs.h"       // Defines core data structures like Property.
#include "file.h"          // Provides file I/O functions (load/save data).
#include "utils.h"         // Contains utility functions like clearConsole, printBanner.
#include "menu.h"          // Manages the application menu system.
#include "localization.h"  // Handles language selection and translation.
#include "test_data.h"     // Generating test data.

/**
 * @brief Application entry point for the Real Estate Agency Management System.
 *
 * This function performs the following critical startup tasks:
 * 1. Initializes the property data storage array and sets the initial count to zero.
 * 2. Loads default language translations (Bulgarian) and then allows the user to select their preferred language.
 * 3. Displays the application welcome banner.
 * 4. Attempts to load previously saved property data from the synchronization text file,
 *    restoring the application state from the last session.
 * 5. If no properties are loaded, prompts the user to generate test data.
 * 6. Enters the main menu loop, allowing the user to interact with the system.
 *
 * @return int Returns 0 upon successful execution and program termination.
 */
int main() {
  Property properties[MAX_PROPERTIES]; // Declares an array to store properties.
  int propertyCount = 0; // Initializes the count of currently loaded properties.

  // Loads default language translations (Bulgarian). This ensures a base language is always set.
  loadTranslations("bg");

  // Displays the application ASCII art banner to the console.
  printBanner();

  // Prompts the user to select their preferred application language.
  selectLanguage();

  // Attempts to load property data from the synchronization file from the last session.
  // This restores the application's working state.
  loadFromSyncTextFile(properties, propertyCount);

  // If the system is empty, ask the user if they want test data.
  if (propertyCount == 0) {
      if (getConfirmation(getTranslatedString("GENERATE_TEST_DATA_PROMPT").c_str())) {
          generateTestProperties(properties, propertyCount);
      }
  }

  // Starts the main menu loop, passing property data and count by reference
  // so menu functions can modify the data.
  mainMenu(properties, propertyCount);

  return 0; // Indicates successful program execution.
}