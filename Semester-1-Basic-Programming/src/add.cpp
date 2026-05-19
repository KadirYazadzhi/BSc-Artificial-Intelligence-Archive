/**
 * @file add.cpp
 * @brief Implementation of functions for adding new properties to the system.
 *
 * This file contains the logic for adding single or multiple properties,
 * including input validation, capacity checks, and data sanitization,
 * thereby ensuring data integrity.
 */

#include <iostream>    // Necessary for standard I/O operations (cout, cin, cerr)
#include <limits>      // Necessary for numeric_limits (used with cin.ignore)
#include <cstring>     // Necessary for C-string manipulation (strlen, strncpy)
#include <type_traits> // Necessary for std::is_arithmetic
#include <string>      // Necessary for std::string manipulation
#include <algorithm>   // Necessary for std::tolower (implicitly used for localized input)

#include "add.h"       // Header for add function declarations
#include "structs.h"   // Defines Property structure and Status enum
#include "update.h"    // Necessary for getPropertyByRefNumber
#include "file.h"      // Necessary for syncDataToRecoveryFiles
#include "colors.h"    // Defines ANSI escape codes for console coloring
#include "localization.h" // Localization functions like getTranslatedString

using namespace std;

/**
 * @brief Sanitizes a C-style string by removing '|' (pipe) characters.
 *
 * Iterates through the input string and constructs a new string
 * in-place that excludes all '|' characters. This is crucial for preventing
 * issues when saving data to pipe-separated text files (e.g. sync.txt),
 * as a '|' character within a data field could corrupt the file format during parsing.
 *
 * @param str The C-style string to sanitize. Modified in-place.
 */
void sanitizeString(char* str) {
    int len = strlen(str);
    int k = 0; // Index for the sanitized string
    for (int i = 0; i < len; i++) {
        if (str[i] != '|') { // Copy only characters that are not '|'.
            str[k++] = str[i];
        }
    }
    str[k] = '\0'; // Terminate the sanitized string with a null character.
}

/**
 * @brief Guides the user through adding a single new property to the system.
 *
 * Prompts the user for all necessary property details,
 * validates the input, checks for unique reference numbers, and then appends
 * the property to the `properties` array. Handles potential errors such as
 * duplicate reference numbers or maximum capacity reached.
 * Upon successful addition, triggers data synchronization for recovery.
 *
 * @param properties Array of `Property` structures where the new property is added.
 * @param propertyCount Reference to an integer representing the current number of properties.
 */
void addSingleProperty(Property properties[], int& propertyCount) {
    // Checks if the maximum property capacity has been reached.
    if (isCapacityReached(propertyCount)) return;

    Property newProperty; // Creates a new Property structure to store input.

    // Gets valid numeric input for the reference number.
    newProperty.refNumber = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_REF_NUMBER") + RESET).c_str());

    // Checks if a property with the same reference number already exists.
    if (getPropertyByRefNumber(newProperty.refNumber, properties, propertyCount) != -1) {
        cout << RED << getTranslatedString("INVALID_DATA") << RESET << endl;
        cout << RED << getTranslatedString("ERROR_REF_NUMBER_EXISTS") << RESET << endl;
        cout << RED << getTranslatedString("ERROR_ADD_PROPERTY_FAILED") << RESET << endl;
        return; // Exits if refNumber is not unique.
    }

    // Gets valid numeric inputs for price, total area, rooms, and floor.
    newProperty.price = getValidNumericInput<double>((CYAN + getTranslatedString("PROMPT_PRICE") + RESET).c_str());
    newProperty.totalArea = getValidNumericInput<double>((CYAN + getTranslatedString("PROMPT_TOTAL_AREA") + RESET).c_str());
    newProperty.rooms = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_ROOMS") + RESET).c_str());
    newProperty.floor = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_FLOOR") + RESET).c_str());

    // Gets valid string inputs for broker, type, area, and exposition.
    // Input strings are sanitized to prevent data corruption.
    getValidStringInput((CYAN + getTranslatedString("PROMPT_BROKER_NAME") + RESET).c_str(), newProperty.broker, sizeof(newProperty.broker));
    getValidStringInput((CYAN + getTranslatedString("PROMPT_PROPERTY_TYPE") + RESET).c_str(), newProperty.type, sizeof(newProperty.type));
    getValidStringInput((CYAN + getTranslatedString("PROMPT_PROPERTY_AREA") + RESET).c_str(), newProperty.area, sizeof(newProperty.area));
    getValidStringInput((CYAN + getTranslatedString("PROMPT_PROPERTY_EXPOSITION") + RESET).c_str(), newProperty.exposition, sizeof(newProperty.exposition));

    newProperty.status = AVAILABLE; // New properties are always initially AVAILABLE.
    properties[propertyCount] = newProperty; // Adds the new property to the array.
    propertyCount++; // Increments the total property count.

    cout << endl;
    cout << GREEN << getTranslatedString("PROPERTY_ADDED_SUCCESS") << RESET << endl;
    syncDataToRecoveryFiles(properties, propertyCount); // Synchronizes recovery data.
}

/**
 * @brief Allows the user to add multiple properties to the system in one session.
 *
 * First prompts the user for the number of properties they wish to add.
 * Then checks if adding that many properties would exceed the system's maximum capacity.
 * If capacity would be exceeded, informs the user and adjusts the number of properties
 * to add to fit the available space. Repeatedly calls `addSingleProperty` for each
 * property to be added.
 *
 * @param properties Array of `Property` structures where new properties are added.
 * @param propertyCount Reference to an integer representing the current number of properties.
 */
void addMultipleProperties(Property properties[], int& propertyCount) {
    // Gets the desired number of properties to add from the user.
    int n = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_NUM_PROPERTIES_TO_ADD") + RESET).c_str());

    // Checks if adding 'n' properties would exceed the maximum capacity.
    if (propertyCount + n > MAX_PROPERTIES) {
        int availableSpace = MAX_PROPERTIES - propertyCount;
        cout << RED << getTranslatedString("ERROR_ADD_EXCEEDS_MAX_PART1") << RESET << endl;
        cout << YELLOW << getTranslatedString("ERROR_ADD_EXCEEDS_MAX_PART2") << " " << availableSpace << " " << getTranslatedString("ERROR_ADD_EXCEEDS_MAX_PART3") << RESET << endl;
        n = availableSpace; // Adjusts 'n' to fit available space.
    }
    
    // If 'n' is zero or less (after adjustment or initial input), checks if capacity is already reached.
    if (n <= 0) {
        isCapacityReached(propertyCount);
        return;
    }

    // Loop to add each property individually.
    for (int i = 0; i < n; i++) {
        cout << YELLOW << "\n--- " << getTranslatedString("PROMPT_ENTERING_PROPERTY") << " #" << (i + 1) << " " << getTranslatedString("PROMPT_OF") << " " << n << " ---" << RESET << endl;
        addSingleProperty(properties, propertyCount); // Calls function to add a single property.
    }
}

/**
 * @brief Checks if the maximum number of properties (MAX_PROPERTIES) has been reached.
 *
 * Compares the current `propertyCount` with `MAX_PROPERTIES`.
 * If the limit is reached, displays localized error messages indicating
 * that no more properties can be added.
 *
 * @param propertyCount The current number of properties in the system.
 * @return `true` if capacity is reached; `false` otherwise.
 */
bool isCapacityReached(int propertyCount) {
    if (propertyCount >= MAX_PROPERTIES) {
        cout << RED << getTranslatedString("ERROR_ADD_NOT_POSSIBLE") << RESET << endl;
        cout << RED << getTranslatedString("ERROR_MAX_CAPACITY_REACHED") << RESET << endl;
        return true;
    }
    return false;
}

/**
 * @brief Prompts the user for string input and stores it in a buffer, with sanitization.
 *
 * Uses `cin.getline` to read a line of text from the user,
 * preventing buffer overflow by limiting input to `bufferSize`. If input
 * exceeds `bufferSize`, displays a warning. After reading, passes the input string
 * to `sanitizeString` to remove any problematic characters (like '|').
 *
 * @param prompt The message displayed to the user when requesting input.
 * @param buffer The character buffer to store the input string.
 * @param bufferSize The maximum size of the buffer, including the null terminator.
 */
void getValidStringInput(const char* prompt, char* buffer, int bufferSize) {
    cout << prompt; // Display prompt.
    cin.getline(buffer, bufferSize); // Read a line of text into the buffer.
    if (cin.fail()) { // Check for input failure (e.g., input too long).
        cin.clear(); // Clear error flags.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining input.
        cout << YELLOW << getTranslatedString("WARNING_INPUT_TRUNCATED") << RESET << endl; // Display warning.
    }
    sanitizeString(buffer); // Sanitize input string.
}
