/**
 * @file search.h
 * @brief Declares functions for searching properties based on various criteria.
 *
 * Provides functionality to filter and display properties matching specific
 * conditions, such as the broker's name or number of rooms.
 */

#ifndef SEARCH_H
#define SEARCH_H

#include "structs.h" // Necessary for Property type

/**
 * @brief Searches and displays properties handled by a specific broker.
 * @param properties Array of Property structures to search in.
 * @param propertyCount The number of properties in the array.
 *
 * Prompts the user for a broker name and then iterates through properties,
 * displaying those that match.
 */
void searchByBroker(Property properties[], int propertyCount);

/**
 * @brief Searches and displays properties based on the number of rooms.
 * @param properties Array of Property structures to search in.
 * @param propertyCount The number of properties in the array.
 *
 * Prompts the user for a number of rooms and then iterates through properties,
 * displaying those that match or exceed the specified number.
 */
void searchByRooms(Property properties[], int propertyCount);

#endif //SEARCH_H