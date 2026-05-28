/**
 * @file reports.cpp
 * @brief Implementation of functions for generating various analytical reports on property data.
 *
 * This file provides the concrete implementation for functions declared in `reports.h`,
 * including finding the most expensive property in a given area, calculating the
 * average price of properties in an area, and determining the percentage of properties
 * sold by each broker. These reports offer valuable insights into the real estate market.
 */

#include <iostream>    // Necessary for standard I/O operations (cout, cin)
#include <cstring>     // Necessary for C-string manipulation (strcmp, strncpy)
#include <iomanip>     // Necessary for output formatting (setprecision, fixed)

#include "reports.h"   // Header with report function declarations
#include "structs.h"   // Defines Property structure and Status enum
#include "display.h"   // Necessary for displayPropertyDetails
#include "colors.h"    // Defines ANSI escape codes for console coloring
#include "add.h"       // Necessary for getValidStringInput
#include "utils.h"     // Necessary for stringsEqualIgnoreCase
#include "localization.h" // Localization functions like getTranslatedString

using namespace std;

/**
 * @brief Finds and displays the most expensive property in a user-specified area.
 *
 * Prompts the user to enter a specific area. Then iterates
 * through the property array to find the one with the highest price
 * that matches the specified area. If no properties are found in the area
 * or if no properties exist in the system, appropriate messages are displayed.
 *
 * @param properties Constant array of `Property` structures for analysis.
 * @param propertyCount The number of valid properties in the array.
 */
void mostExpensiveInArea(const Property properties[], int propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }

    char searchArea[50];
    // Get valid string for the search area using localized prompt.
    getValidStringInput((CYAN + getTranslatedString("PROMPT_REPORT_AREA") + RESET).c_str(), searchArea, sizeof(searchArea));

    double maxPrice = -1.0; // Initialize with impossible price to ensure any valid price is greater.
    int mostExpensiveIndex = -1; // Initialize with -1 to indicate no property found yet.

    // Iterate through all properties to find the most expensive one in the specified area.
    for (int i = 0; i < propertyCount; i++) {
        // Compare the current property's area with the search area (case-insensitive).
        if (stringsEqualIgnoreCase(properties[i].area, searchArea)) {
            // If the current property's price is higher than current maxPrice, update.
            if (properties[i].price > maxPrice) {
                maxPrice = properties[i].price;
                mostExpensiveIndex = i; // Store the index of this most expensive property.
            }
        }
    }

    // Check if any property was found in the specified area.
    if (mostExpensiveIndex == -1) {
        cout << endl;
        cout << RED << getTranslatedString("NO_PROPERTY_FOUND_IN_AREA") << RESET << endl;
        return;
    }

    cout << YELLOW << "\n--- " << getTranslatedString("MOST_EXPENSIVE_PROPERTY_IN_AREA") << " " << searchArea << " ---" << RESET << endl;
    // Display details of the found most expensive property.
    displayPropertyDetails(properties[mostExpensiveIndex]);
}

/**
 * @brief Calculates and displays the average price of properties in a user-specified area.
 *
 * Prompts the user for an area. Then iterates through all properties,
 * summing the prices of properties in that area and counting how many of them
 * exist. Finally, calculates and displays the average price,
 * or an error message if no properties are found in the area or if the system is empty.
 *
 * @param properties Constant array of `Property` structures for analysis.
 * @param propertyCount The number of valid properties in the array.
 */
void averagePriceInArea(const Property properties[], int propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }

    char searchArea[50];
    // Get valid string for the search area using localized prompt.
    getValidStringInput((CYAN + getTranslatedString("PROMPT_REPORT_AREA") + RESET).c_str(), searchArea, sizeof(searchArea));

    double totalPrice = 0.0;     // Accumulator for total price of properties in the area.
    int propertiesInAreaCount = 0; // Counter for found properties in the area.

    // Iterate through all properties to sum prices and count properties in the specified area.
    for (int i = 0; i < propertyCount; i++) {
        if (stringsEqualIgnoreCase(properties[i].area, searchArea)) {
            totalPrice += properties[i].price;
            propertiesInAreaCount++;
        }
    }

    // Check if properties were found in the specified area.
    if (propertiesInAreaCount == 0) {
        cout << RED << getTranslatedString("NO_PROPERTIES_FOUND_IN_AREA") << RESET << endl;
        return;
    }

    cout << YELLOW << "\n--- " << getTranslatedString("FOUND_PROPERTIES_COUNT_PART1") << " " << propertiesInAreaCount << " " << getTranslatedString("FOUND_PROPERTIES_COUNT_PART2") << " " << totalPrice << " ---" << RESET << endl;
    cout << getTranslatedString("AVERAGE_PRICE_IN_AREA_PART1") << " '" << searchArea << " ' " << getTranslatedString("AVERAGE_PRICE_IN_AREA_PART2") << " " << fixed << setprecision(2) << totalPrice / propertiesInAreaCount << "." << endl;
}

/**
 * @brief Calculates and displays the percentage of properties sold for each unique broker.
 *
 * Efficiently gathers statistics for each broker using `std::map`.
 * Iterates through all properties, incrementing total and sold counts for each broker.
 * This approach dynamically handles any number of unique brokers without fixed-size array limits.
 * Finally, presents the sold percentage for each broker, offering valuable insights
 * into individual broker performance.
 *
 * @param properties Constant array of `Property` structures for analysis.
 * @param propertyCount The number of valid properties in the array.
 */
void soldPercentagePerBroker(const Property properties[], int propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }

    // Parallel arrays to store statistics.
    // Since we don't know upfront how many unique brokers there are, we allocate an array
    // with the maximum possible size (equal to property count).
    char brokerNames[MAX_PROPERTIES][50];
    int totalProperties[MAX_PROPERTIES] = {0}; // Initialize with zeros
    int soldProperties[MAX_PROPERTIES] = {0};
    int uniqueBrokersCount = 0;

    // Iterate through all properties
    for (int i = 0; i < propertyCount; i++) {
        const Property& prop = properties[i];
        
        // Check if this broker is already in the list
        int brokerIndex = -1;
        for (int j = 0; j < uniqueBrokersCount; j++) {
            if (strcmp(brokerNames[j], prop.broker) == 0) {
                brokerIndex = j;
                break;
            }
        }

        // If broker is new, add them
        if (brokerIndex == -1) {
            brokerIndex = uniqueBrokersCount;
            strncpy(brokerNames[brokerIndex], prop.broker, 49);
            brokerNames[brokerIndex][49] = '\0';
            uniqueBrokersCount++;
        }

        // Update statistics
        totalProperties[brokerIndex]++;
        if (prop.status == SOLD) {
            soldProperties[brokerIndex]++;
        }
    }

    cout << YELLOW << "\n--- " << getTranslatedString("SOLD_PERCENTAGE_PER_BROKER_HEADER") << " ---" << RESET << endl;

    // Display results
    for (int i = 0; i < uniqueBrokersCount; i++) {
        double soldBrokerPercentage = 0.0;
        if (totalProperties[i] > 0) {
            soldBrokerPercentage = (static_cast<double>(soldProperties[i]) / totalProperties[i]) * 100.0;
        }

        cout << getTranslatedString("BROKER_LABEL") << ": " << brokerNames[i] << endl;
        cout << left; // Align output to the left.
        cout << "  " << setw(20) << getTranslatedString("TOTAL_PROPERTIES_LABEL") << totalProperties[i] << endl;
        cout << "  " << setw(20) << getTranslatedString("SOLD_PROPERTIES_LABEL") << soldProperties[i] << endl;
        cout << "  " << setw(20) << getTranslatedString("SOLD_PERCENTAGE_LABEL") << fixed << setprecision(2) << soldBrokerPercentage << "%" << endl;
        cout << endl;
    }
}
