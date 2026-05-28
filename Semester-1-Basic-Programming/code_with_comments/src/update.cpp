/**
 * @file update.cpp
 * @brief Implementation of my functions for modifying existing property records in the system.
 *
 * Here I provide the concrete implementation for functions declared in `update.h`,
 * allowing users to search for a property by its reference number and then update
 * various attributes. I include robust input validation, checks for unique reference
 * numbers, and handle special conditions like modifying property status.
 */

#include <iostream>    // Necessary for standard I/O operations (cout, cin)
#include <cstring>     // Necessary for C-string manipulation (strcmp, strncpy)
#include <limits>      // Necessary for numeric_limits (used with cin.ignore)
#include <string>      // Necessary for std::string manipulation (to_string)
#include <iomanip>     // Necessary for output formatting (setw)

#include "update.h"    // Header with update/edit function declarations
#include "structs.h"   // Defines Property structure and Status enum
#include "file.h"      // Necessary for syncDataToRecoveryFiles
#include "colors.h"    // Defines ANSI escape codes for console coloring
#include "add.h"       // Necessary for getValidNumericInput and getValidStringInput
#include "localization.h" // Localization functions like getTranslatedString

using namespace std;

/**
 * @brief Main function with which I update the details of an existing property.
 *
 * I guide the user through the property update process.
 * First I prompt for a property reference number, then verify its existence.
 * If I find the property and it is not marked as SOLD, I present a menu of fields
 * that can be updated. Based on the user's choice, I call the appropriate helper
 * function to modify the specific field. Upon successful update, data is
 * synchronized for recovery.
 *
 * @param properties Array of `Property` structures where the property to update is located.
 * @param propertyCount The current number of valid properties in the array.
 */
void updateProperty(Property properties[], int& propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }
    
    // Prompt for reference number of the property to update.
    int refNumber = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_REF_NUMBER_TO_UPDATE") + RESET).c_str());
    // Find index of property in array.
    int index = getPropertyByRefNumber(refNumber, properties, propertyCount);

    if (index == -1) {
        cout << RED << getTranslatedString("ERROR_PROPERTY_NOT_FOUND_REF") << " - " << refNumber << "." << RESET << endl;
        return;
    }

    // Prevent editing of already SOLD properties.
    if (properties[index].status == SOLD) {
        cout << RED << getTranslatedString("ERROR_SOLD_PROPERTY_CANNOT_BE_EDITED") << RESET << endl;
        return;
    }

    // Show menu with editable fields, using localized strings for clarity.
    cout << CYAN << getTranslatedString("UPDATE_MENU_CHOOSE_FIELD") << RESET << endl;
    cout << left; // Align menu options to left.
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_REF_NUMBER") << getTranslatedString("UPDATE_MENU_PRICE") << endl;
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_BROKER") << getTranslatedString("UPDATE_MENU_TOTAL_AREA") << endl;
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_TYPE") << getTranslatedString("UPDATE_MENU_ROOMS") << endl;
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_AREA") << getTranslatedString("UPDATE_MENU_FLOOR") << endl;
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_EXPOSITION") << getTranslatedString("UPDATE_MENU_STATUS") << endl;
    cout << "  " << getTranslatedString("ADD_MENU_BACK") << endl; // Option to go back.

    // Get user's choice for field to update.
    int choice = getValidNumericInput<int>((CYAN + getTranslatedString("ENTER_YOUR_CHOICE") + RESET).c_str());

    bool updateMade = false; // Flag to track if a successful update was made.
    switch (choice) {
        case 1: updateMade = updateRefNumber(properties, propertyCount, index); break;
        case 2: updateMade = updateStringField(properties[index].broker, 50, getTranslatedString("BROKER_FIELD_NAME").c_str()); break;
        case 3: updateMade = updateStringField(properties[index].type, 50, getTranslatedString("TYPE_FIELD_NAME").c_str()); break;
        case 4: updateMade = updateStringField(properties[index].area, 50, getTranslatedString("AREA_FIELD_NAME").c_str()); break;
        case 5: updateMade = updateStringField(properties[index].exposition, 20, getTranslatedString("EXPOSITION_FIELD_NAME").c_str()); break;
        case 6: updateMade = updateNumericField(&properties[index].price, getTranslatedString("PRICE_FIELD_NAME").c_str()); break;
        case 7: updateMade = updateNumericField(&properties[index].totalArea, getTranslatedString("TOTAL_AREA_FIELD_NAME").c_str()); break;
        case 8: updateMade = updateNumericField(&properties[index].rooms, getTranslatedString("ROOMS_FIELD_NAME").c_str()); break;
        case 9: updateMade = updateNumericField(&properties[index].floor, getTranslatedString("FLOOR_FIELD_NAME").c_str()); break;
        case 10: updateMade = updateStatus(properties[index]); break;
        case 0: return; // User chose to go back.
        default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break;
    }

    if (updateMade) {
        cout << GREEN << getTranslatedString("PROPERTY_DATA_UPDATED_SUCCESS") << RESET << endl;
        syncDataToRecoveryFiles(properties, propertyCount); // Synchronize data if update occurred.
    }
}

/**
 * @brief Searches for a property by its reference number.
 *
 * I use this helper function from various modules to locate a specific property.
 * I iterate through the property array and return the index of the matching
 * property. If I don't find a property with the given reference number, I return -1.
 *
 * @param refNumber The reference number of the property to find.
 * @param properties Constant array of `Property` structures to search.
 * @param propertyCount The number of valid properties in the array.
 * @return 0-based index of the property if found; otherwise -1.
 */
int getPropertyByRefNumber(int refNumber, const Property properties[], int propertyCount) {
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].refNumber == refNumber) return i;
    }
    return -1; // Property not found.
}

/**
 * @brief Updates a property's reference number, ensuring uniqueness.
 *
 * I prompt the user for a new reference number. I check if
 * the new reference number is different from the old one and, more importantly,
 * if it is unique within the existing property array. If valid and unique,
 * I update the property's reference number.
 *
 * @param properties Array of `Property` structures (needed for uniqueness check).
 * @param propertyCount The number of valid properties in the array.
 * @param index The index of the property whose reference number is to be updated.
 * @return `true` if the reference number is successfully updated; `false` otherwise.
 */
bool updateRefNumber(Property properties[], int propertyCount, int index) {
    // Get new reference number from user.
    int newRefNumber = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_NEW_REF_NUMBER") + RESET).c_str());

    // Check if new reference number is identical to current.
    if (properties[index].refNumber == newRefNumber) {
         cout << YELLOW << getTranslatedString("WARNING_VALUE_IDENTICAL") << RESET << endl;
        return false;
    }

    // Check if new reference number already exists (must be unique).
    if (getPropertyByRefNumber(newRefNumber, properties, propertyCount) != -1) {
        cout << RED << getTranslatedString("ERROR_INVALID_OPERATION_REF_EXISTS") << RESET << endl;
        return false;
    }

    properties[index].refNumber = newRefNumber; // Update reference number.
    return true;
}

/**
 * @brief Updates a property's string field with new user input.
 *
 * I prompt the user for a new string value for a specified field.
 * I use `getValidStringInput` for safe input and sanitization. I check
 * if the new value is identical to the current one to avoid unnecessary updates.
 *
 * @param fieldPtr Pointer to the character array field to be updated (e.g. `property.broker`).
 * @param maxSize The maximum size of the character array (including null terminator).
 * @param fieldName Localized name of the field being updated (for user prompts).
 * @return `true` if the field was updated; `false` if the user provided the same value.
 */
bool updateStringField(char* fieldPtr, int maxSize, const char* fieldName) {
    char newValue[MAX_STRING_SIZE]; // Use MAX_STRING_SIZE from update.h
    // Construct localized prompt including field name and max char limit.
    string prompt = string(CYAN) + getTranslatedString("PROMPT_NEW_VALUE_FOR") + " " + fieldName + " (" + getTranslatedString("UP_TO") + " " + to_string(maxSize - 1) + " " + getTranslatedString("CHARACTERS") + "): " + RESET;
    // Get valid and sanitized string.
    getValidStringInput(prompt.c_str(), newValue, sizeof(newValue));

    // Check if new value is identical to current value.
    if (strcmp(fieldPtr, newValue) == 0) {
        cout << YELLOW << getTranslatedString("WARNING_VALUE_IDENTICAL") << RESET << endl;
        return false;
    }

    // Copy new value safely into field, ensuring null termination.
    strncpy(fieldPtr, newValue, maxSize - 1);
    fieldPtr[maxSize - 1] = '\0'; // Ensure null termination
    return true;
}


/**
 * @brief Updates a property's status, with special logic for price when RESERVED.
 *
 * I present a menu to choose a new status (AVAILABLE, SOLD, RESERVED).
 * I validate user input and apply the new status. Here I have implemented a specific business rule:
 * if a property goes from AVAILABLE to RESERVED, I reduce its price by 20%. This logic
 * is crucial for implementing specific pricing strategies for reserved properties.
 *
 * @param propertyToUpdate Reference to the `Property` structure whose status is to be updated.
 * @return `true` if status was updated; `false` if new status is identical to old or input invalid.
 */
bool updateStatus(Property& propertyToUpdate) {
    Status oldStatus = propertyToUpdate.status; // Store old status for comparison.

    // Show localized menu for new status options.
    cout << CYAN << getTranslatedString("PROMPT_SELECT_NEW_STATUS") << RESET << endl;
    cout << left;
    cout << "  " << setw(15) << getTranslatedString("STATUS_AVAILABLE") << endl;
    cout << "  " << setw(15) << getTranslatedString("STATUS_SOLD") << endl;
    cout << "  " << setw(15) << getTranslatedString("STATUS_RESERVED") << endl;
    
    int choice;
    // Loop to get and validate user's status choice.
    while (true) {
        choice = getValidNumericInput<int>((CYAN + getTranslatedString("ENTER_YOUR_CHOICE") + RESET).c_str());
        if (choice >= 1 && choice <= 3) break; // Valid choices are 1, 2, or 3.
        cout << RED << getTranslatedString("ERROR_INVALID_STATUS_CHOICE") << RESET << endl;
    }

    Status newStatus;
    switch (choice) {
        case 1: newStatus = AVAILABLE; break;
        case 2: newStatus = SOLD; break;
        case 3: newStatus = RESERVED; break;
        default: return false; // Should theoretically not be reached due to validation loop.
    }

    // Check if new status is identical to old.
    if (oldStatus == newStatus) {
        cout << YELLOW << getTranslatedString("WARNING_STATUS_IDENTICAL") << RESET << endl;
        return false;
    }

    // Apply specific business logic: 20% price reduction when moving from AVAILABLE to RESERVED.
    if (oldStatus == AVAILABLE && newStatus == RESERVED) {
        propertyToUpdate.price *= 0.8; // Reduce price by 20%.
        cout << YELLOW << getTranslatedString("WARNING_PRICE_REDUCED_RESERVED") << RESET << endl;
    }

    propertyToUpdate.status = newStatus; // Update property status.
    return true;
}
