/**
* @file search.cpp
 * @brief Implementation of functions for searching and filtering properties by various criteria.
 *
 * This file provides the concrete implementation of functions declared in `search.h`,
 * allowing users to search properties by broker name or by number of rooms.
 * Search results are sorted by price to help users
 * analyze and compare listings.
 */

#include <iostream>    // Necessary for standard I/O operations (cout, cin)
#include <limits>      // Necessary for numeric_limits (used with cin.ignore)
#include <cstring>     // Necessary for C-string manipulation (strcmp)
#include <algorithm>   // Necessary for algorithms like sort (not used directly here due to custom sort)

#include "search.h"    // Header with search function declarations
#include "structs.h"   // Defines Property structure and Status enum
#include "display.h"   // Necessary for displayPropertyDetails
#include "sort.h"      // Necessary for sortPropertiesArray
#include "colors.h"    // Defines ANSI escape codes for console coloring
#include "add.h"       // Necessary for getValidNumericInput and getValidStringInput
#include "utils.h"     // Necessary for stringsEqualIgnoreCase
#include "localization.h" // Localization functions like getTranslatedString

using namespace std;

/**
 * @brief Searches and displays properties handled by a specific broker.
 *
 * Prompts the user for a broker name. Then iterates through the
 * property array, copying all properties managed by the specified broker
 * into a temporary array. If properties are found, further prompts the user
 * to choose a sort order (ascending or descending by price) and then displays
 * the found properties.
 *
 * @param properties Array of `Property` structures to search.
 * @param propertyCount The number of valid properties in the array.
 */
void searchByBroker(Property properties[], int propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }

    char searchBroker[50];
    // Get valid string for the search broker name using localized prompt.
    getValidStringInput((CYAN + getTranslatedString("PROMPT_SEARCH_BROKER_NAME") + RESET).c_str(), searchBroker, sizeof(searchBroker));

    Property tempProperties[MAX_PROPERTIES]; // Temporary array to store matching properties.
    int tempCount = 0;                       // Count of properties in the temporary array.
    bool isFound = false;                    // Flag to track if properties are found.

    // Iterate through all properties to find matches for the specified broker.
    for (int i = 0; i < propertyCount; i++) {
        if (stringsEqualIgnoreCase(searchBroker, properties[i].broker)) {
            tempProperties[tempCount] = properties[i]; // Copy matching property to temp array.
            tempCount++;
            isFound = true; // Set flag to true as at least one property found.
        }
    }

    // If no properties found for the given broker, display message and return.
    if (!isFound) {
        cout << RED << getTranslatedString("NO_PROPERTIES_FOUND_FOR_BROKER") << " '" << searchBroker << "'." << RESET << endl;
        return;
    }

    cout << CYAN << getTranslatedString("PROMPT_SORT_ORDER_BY_PRICE") << RESET << endl;
    cout << getTranslatedString("SORT_ORDER_ASCENDING") << endl;
    cout << getTranslatedString("SORT_ORDER_DESCENDING") << endl;
    
    int choice;
    bool isAscending;
    // Loop to get and validate user's sort order choice.
    while (true) {
        choice = getValidNumericInput<int>((CYAN + getTranslatedString("ENTER_YOUR_CHOICE") + RESET).c_str());
        if (choice == 1 || choice == 2) {
            isAscending = (choice == 1); // 1 for ascending, 2 for descending.
            break;
        }
        cout << RED << getTranslatedString("ERROR_INVALID_SORT_CHOICE") << RESET << endl;
    }

    // Sort found properties by price based on user choice.
    sortPropertiesArray(tempProperties, tempCount, isAscending);

    cout << YELLOW << "\n--- " << getTranslatedString("SEARCH_RESULTS_FOR_BROKER") << " '" << searchBroker << "' (" << getTranslatedString("SORTED_BY_PRICE") << ") ---" << RESET << endl;
    // Display details of each found and sorted property.
    for (int i = 0; i < tempCount; i++) {
        cout << YELLOW << "--- " << getTranslatedString("PROPERTY_HEADER") << " #" << i + 1 << RESET << endl;
        displayPropertyDetails(tempProperties[i]);
    }
}

/**
 * @brief Searches and displays properties based on the number of rooms.
 *
 * Prompts the user for a number of rooms. Then iterates through the
 * property array, copying all properties that match the specified room count
 * into a temporary array. If properties are found, they are sorted
 * by price (descending by default, as indicated by `false` in `sortPropertiesArray` call)
 * and then displayed to the user.
 *
 * @param properties Array of `Property` structures to search.
 * @param propertyCount The number of valid properties in the array.
 */
void searchByRooms(Property properties[], int propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }

    int roomsCount = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_SEARCH_ROOMS_COUNT") + RESET).c_str());

    Property tempProperties[MAX_PROPERTIES]; // Temporary array to store matching properties.
    int tempCount = 0;                       // Count of properties in the temporary array.
    bool isFound = false;                    // Flag to track if properties are found.

    // Iterate through all properties to find matches for the specified number of rooms.
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].rooms == roomsCount) {
            tempProperties[tempCount] = properties[i]; // Copy matching property to temp array.
            tempCount++;
            isFound = true; // Set flag to true as at least one property found.
        }
    }

    // If no properties found for the given room count, display message and return.
    if (!isFound) {
        cout << RED << getTranslatedString("NO_PROPERTIES_FOUND_FOR_ROOMS_COUNT_PART1") << " " << roomsCount << " " << getTranslatedString("NO_PROPERTIES_FOUND_FOR_ROOMS_COUNT_PART2") << RESET << endl;
        return;
    }

    // Sort found properties by price in descending order.
    sortPropertiesArray(tempProperties, tempCount, false);
    
    cout << YELLOW << "\n--- " << getTranslatedString("SEARCH_RESULTS_FOR_ROOMS_COUNT_PART1") << " " << roomsCount << " " << getTranslatedString("SEARCH_RESULTS_FOR_ROOMS_COUNT_PART2") << " (" << getTranslatedString("SORTED_BY_PRICE") << ") ---" << RESET << endl;
    // Display details of each found and sorted property.
    for (int i = 0; i < tempCount; i++) {
        cout << YELLOW << "--- " << getTranslatedString("PROPERTY_HEADER") << " #" << i + 1 << RESET << endl;
        displayPropertyDetails(tempProperties[i]);
    }
}
