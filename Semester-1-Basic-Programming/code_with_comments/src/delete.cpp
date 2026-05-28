/**
 * @file delete.cpp
 * @brief Implementation of functions for deleting property records from the system.
 *
 * This file provides the concrete implementation for functions declared in `delete.h`,
 * allowing users to remove individual properties by reference number or clear
 * all properties from the system, with appropriate user confirmations and
 * recovery data synchronization.
 */

#include <iostream>    // Necessary for standard I/O operations (cout, cin)
#include <cctype>      // Necessary for tolower (used in getConfirmation)
#include <limits>      // Necessary for numeric_limits (used with cin.ignore)
#include <string>      // Necessary for std::to_string

#include "delete.h"    // Header for delete function declarations
#include "structs.h"   // Defines Property structure
#include "update.h"    // Necessary for getPropertyByRefNumber
#include "file.h"      // Necessary for syncDataToRecoveryFiles
#include "colors.h"    // Defines ANSI escape codes for console coloring
#include "add.h"       // Necessary for getValidNumericInput
#include "utils.h"     // Necessary for getConfirmation
#include "localization.h" // Localization functions like getTranslatedString

using namespace std;

/**
 * @brief Deletes a single property from the system based on its reference number.
 *
 * First checks if there are properties to delete. Then
 * prompts the user for a property reference number, searches for it, and
 * if found, requests confirmation before proceeding with deletion.
 * Upon confirmation, removes the property by shifting subsequent elements
 * in the array, and decrements `propertyCount`. Then synchronizes data
 * for recovery purposes.
 *
 * @param properties Array of `Property` structures to delete from.
 * @param propertyCount Reference to an integer representing the current number of properties.
 */
void DeleteProperty(Property properties[], int& propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_TO_DELETE") << RESET << endl;
        return;
    }

    // Prompt for reference number of the property to delete.
    int refNumber = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_REF_NUMBER_TO_DELETE") + RESET).c_str());

    // Find the index of the property by its reference number.
    int index = getPropertyByRefNumber(refNumber, properties, propertyCount);
    if (index == -1) {
        cout << RED << getTranslatedString("ERROR_PROPERTY_NOT_FOUND_REF") << RESET << endl;
        return;
    }

    // Request user confirmation before deleting the property.
    if (!getConfirmation((getTranslatedString("CONFIRM_DELETE_PROPERTY_PART1") + " - " + to_string(refNumber) + "? [y/n]: ").c_str())) {
        cout << YELLOW << getTranslatedString("DELETE_CANCELLED") << RESET << endl;
        return;
    }

    // Shift elements to fill the gap created by the deleted property.
    for (int i = index; i < propertyCount - 1; i++) {
        properties[i] = properties[i + 1];
    }

    propertyCount--; // Decrement total property count.

    cout << GREEN << getTranslatedString("PROPERTY_DELETED_SUCCESS_PART1") << " " << refNumber << " " << getTranslatedString("PROPERTY_DELETED_SUCCESS_PART2") << RESET << endl;
    syncDataToRecoveryFiles(properties, propertyCount); // Synchronize recovery data.
}

/**
 * @brief Deletes all properties currently stored in the system.
 *
 * First checks if there are properties to delete. Then
 * requests explicit user confirmation before clearing all properties.
 * Upon confirmation, resets `propertyCount` to zero, effectively clearing
 * the property array. Then synchronizes data for recovery purposes.
 * This operation is irreversible without recovery from backup files.
 *
 * @param properties Array of `Property` structures to be cleared. (Content is logically cleared by propertyCount = 0)
 * @param propertyCount Reference to an integer representing the current number of properties.
 */
void DeleteAllProperties(Property properties[], int& propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_TO_DELETE") << RESET << endl;
        return;
    }

    // Request user confirmation before deleting all properties.
    if (!getConfirmation(getTranslatedString("CONFIRM_DELETE_ALL_PROPERTIES").c_str())) {
        cout << YELLOW << getTranslatedString("DELETE_ALL_CANCELLED") << RESET << endl;
        return;
    }

    propertyCount = 0; // Resets propertyCount to 0, effectively deleting all properties.

    cout << GREEN << getTranslatedString("ALL_PROPERTIES_DELETED_SUCCESS") << RESET << endl;
    syncDataToRecoveryFiles(properties, propertyCount); // Synchronize recovery data.
}