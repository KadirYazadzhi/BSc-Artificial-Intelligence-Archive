/**
 * @file delete.h
 * @brief Declares functions for deleting property records from the system.
 *
 * Provides functionality to remove a single property by its reference number
 * or to clear all properties currently stored in the system, with user confirmation.
 */

#ifndef DELETE_H
#define DELETE_H

#include "structs.h" // Necessary for Property type

/**
 * @brief Deletes a single property from the system based on its reference number.
 * @param properties Array of Property structures to delete from.
 * @param propertyCount Reference to an integer representing the current number of properties.
 *
 * Prompts the user for a property reference number, confirms deletion,
 * and then shifts array elements to maintain continuity.
 */
void DeleteProperty(Property properties[], int& propertyCount);

/**
 * @brief Deletes all properties currently stored in the system.
 * @param properties Array of Property structures to be cleared.
 * @param propertyCount Reference to an integer representing the current number of properties.
 *
 * Requires explicit user confirmation to prevent accidental data loss.
 * Effectively resets the property list to an empty state.
 */
void DeleteAllProperties(Property properties[], int& propertyCount);

#endif //DELETE_H