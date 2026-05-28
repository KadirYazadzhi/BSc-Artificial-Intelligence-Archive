/**
 * @file display.h
 * @brief Declares functions responsible for displaying property information.
 *
 * Provides functionality to list all properties, filter and show sold properties,
 * display the largest properties, and present detailed information for a single property.
 * Also includes a utility to check if the property list is empty.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "structs.h" // Necessary for Property type

/**
 * @brief Displays all properties currently stored in the system.
 * @param properties Array of Property structures to display.
 * @param propertyCount The number of properties in the array.
 *
 * Iterates through the entire list of properties and calls
 * `displayPropertyDetails` for each one.
 */
void displayAllProperties(const Property properties[], int propertyCount);

/**
 * @brief Displays only properties that are marked as SOLD.
 * @param properties Array of Property structures to filter and display.
 * @param propertyCount The number of properties in the array.
 *
 * Helps users quickly identify properties that are no longer available.
 */
void displaySoldProperties(const Property properties[], int propertyCount);

/**
 * @brief Displays properties sorted by their total area in descending order.
 * @param properties Array of Property structures to sort and display.
 * @param propertyCount The number of properties in the array.
 *
 * Typically makes a temporary copy for sorting without altering the original order,
 * then displays the details of the largest properties.
 */
void displayLargestProperties(const Property properties[], int propertyCount);

/**
 * @brief Displays detailed information for a single property.
 * @param prop Constant reference to the Property structure to display.
 *
 * A helper function used by other display functions to ensure consistent
 * formatting of property details.
 */
void displayPropertyDetails(const Property& prop);

/**
 * @brief Checks if there are any properties loaded in the system.
 * @param propertyCount The current number of properties in the system.
 * @return true if no properties are loaded (propertyCount is 0), false otherwise.
 *
 * Used to prevent operations on an empty list and provide appropriate feedback to the user.
 */
bool isPropertiesEmpty(int propertyCount);


#endif //DISPLAY_H