/**
 * @file display.cpp
 * @brief Implementation of functions responsible for displaying property information on the console.
 *
 * This file provides the concrete implementation for functions declared in `display.h`,
 * allowing the presentation of property details in various formats, such as
 * listing all properties, filtering sold properties, identifying the largest properties,
 * and displaying individual property details. Also includes a utility to check
 * if the property list is empty before attempting display operations.
 */

#include <iostream>    // Necessary for standard I/O operations (cout)
#include <iomanip>     // Necessary for output formatting (setw, fixed, setprecision)

#include "display.h"   // Header for display function declarations
#include "structs.h"   // Defines Property structure and Status enum
#include "colors.h"    // Defines ANSI escape codes for console coloring
#include "localization.h" // Localization functions like getTranslatedString

using namespace std;

/**
 * @brief Checks if there are any properties loaded in the system.
 *
 * This function is a common guard for display and other property-related
 * operations. If `propertyCount` is zero, a localized error message is printed
 * indicating that no properties are available for the requested operation.
 *
 * @param propertyCount The current number of properties in the system.
 * @return `true` if no properties are loaded (propertyCount is 0); `false` otherwise.
 */
bool isPropertiesEmpty(int propertyCount) {
    if (propertyCount == 0) {
        cout << RED << getTranslatedString("ERROR_OPERATION_NOT_POSSIBLE_NO_PROPERTIES") << RESET << endl;
        return true;
    }
    return false;
}

/**
 * @brief Displays detailed information for a single property on the console.
 *
 * Formats and prints all attributes of a given `Property` structure.
 * Uses `iomanip` for consistent spacing and floating-point precision, and
 * `localization.h` to display field names and status in the current language.
 * This ensures a standardized and user-friendly presentation of property data.
 *
 * @param prop Constant reference to the `Property` structure whose details are to be displayed.
 */
void displayPropertyDetails(const Property &prop) {
    cout << left; // Align text to the left.
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_REF_NUMBER") << prop.refNumber << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_BROKER_NAME") << prop.broker << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_TYPE") << prop.type << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_AREA") << prop.area << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_EXPOSITION") << prop.exposition << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_PRICE") << fixed << setprecision(2) << prop.price << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_TOTAL_AREA") << fixed << setprecision(2) << prop.totalArea << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_ROOMS") << prop.rooms << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_FLOOR") << prop.floor << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_STATUS") << getStatusString(prop.status) << endl;
    cout << endl;
}

/**
 * @brief Displays all properties currently stored in the system.
 *
 * First checks if the property list is empty. If not,
 * iterates through the entire array of properties and calls
 * `displayPropertyDetails` for each one. Each property is preceded by a
 * localized header indicating its sequential number in the list.
 *
 * @param properties Constant array of `Property` structures to display.
 * @param propertyCount The number of valid properties in the array.
 */
void displayAllProperties(const Property properties[], int propertyCount) {
    if (isPropertiesEmpty(propertyCount)) return; // Check if there are properties to display.

    // Iterate through each property and display its details.
    for (int i = 0; i < propertyCount; i++) {
        cout << YELLOW << "--- " << getTranslatedString("PROPERTY_HEADER") << " #" << i + 1 << " ---" << RESET << endl;
        displayPropertyDetails(properties[i]);
    }
}

/**
 * @brief Displays only properties that are marked as SOLD.
 *
 * Checks if the property list is empty. If not, iterates
 * through all properties, displaying only those whose `status` is `SOLD`.
 * Includes a localized header and a count of found sold properties.
 * If no sold properties are found, displays a specific localized message.
 *
 * @param properties Constant array of `Property` structures to filter and display.
 * @param propertyCount The number of valid properties in the array.
 */
void displaySoldProperties(const Property properties[], int propertyCount) {
    if (isPropertiesEmpty(propertyCount)) return; // Check if there are properties to display.

    bool isFound = false; // Flag to track if sold properties are found.
    int foundCount = 0;   // Counter for displayed sold properties.

    // Iterate through properties, looking for those with SOLD status.
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].status == SOLD) {
            if (!isFound) { // Print header only once when the first sold property is found.
                cout << YELLOW << "--- " << getTranslatedString("SOLD_PROPERTIES_HEADER") << " ---" << RESET << endl;
                isFound = true;
            }
            cout << YELLOW << "#" << ++foundCount << RESET << endl; // Display sequential number.
            displayPropertyDetails(properties[i]);
        }
    }

    // If no sold properties were found after checking all.
    if (!isFound) {
        cout << YELLOW << getTranslatedString("NO_SOLD_PROPERTIES_CURRENTLY") << RESET << endl;
    }
}

/**
 * @brief Displays properties with the largest total area.
 *
 * First checks if the property list is empty. If not, determines
 * the maximum `totalArea` among all properties. Then iterates through the
 * properties again, displaying details of all properties that match this
 * maximum area. Handles cases where no properties have positive area.
 *
 * @param properties Constant array of `Property` structures for analysis and display.
 * @param propertyCount The number of valid properties in the array.
 */
void displayLargestProperties(const Property properties[], int propertyCount) {
    if (isPropertiesEmpty(propertyCount)) return; // Check if there are properties to display.

    double maxTotalArea = 0.0; // Initialize max area to 0.0.
    // First pass: find the maximum total area among all properties.
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].totalArea > maxTotalArea) {
            maxTotalArea = properties[i].totalArea;
        }
    }

    // If no properties with area greater than 0, display message.
    if (maxTotalArea == 0.0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_WITH_AREA_GREATER_THAN_ZERO") << RESET << endl;
        return;
    }

    cout << YELLOW << "--- " << getTranslatedString("LARGEST_PROPERTIES_HEADER") << " (" << fixed << setprecision(2) << maxTotalArea << " " << getTranslatedString("SQ_M") << ") ---" << RESET << endl;
    int foundCount = 0; // Counter for displayed largest properties.
    // Second pass: display properties that match the maximum total area.
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].totalArea == maxTotalArea) {
            cout << YELLOW << "#" << ++foundCount << RESET << endl; // Display sequential number.
            displayPropertyDetails(properties[i]);
        }
    }
}