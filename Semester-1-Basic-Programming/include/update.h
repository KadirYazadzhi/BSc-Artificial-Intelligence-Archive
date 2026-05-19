/**
 * @file update.h
 * @brief Declares functions responsible for modifying existing property records.
 *
 * Provides functionality to search for a property by its reference number
 * and then update various attributes of that property, ensuring data integrity
 * through validation.
 */

#ifndef UPDATE_H
#define UPDATE_H

#include "structs.h" // Necessary for Property type
#include <iostream>  // Necessary for cin, cout in template function
#include <limits>    // Necessary for numeric_limits in template function

// Defines the maximum size for string fields in the Property structure (including null terminator).
#define MAX_STRING_SIZE 51 // 50 for data + 1 for '\0'

/**
 * @brief Main function for updating an existing property's details.
 * @param properties Array of Property structures.
 * @param propertyCount The current number of properties in the system.
 *
 * Prompts the user to enter a reference number, searches for the property,
 * and then allows the user to choose which fields to update.
 */
void updateProperty(Property properties[], int& propertyCount);

/**
 * @brief Searches for a property by its reference number.
 * @param refNumber The reference number of the property to find.
 * @param properties Array of Property structures to search in.
 * @param propertyCount The number of properties in the array.
 * @return The index of the property in the array if found, otherwise -1.
 *
 * This helper function is critical for various operations requiring the location of a specific property.
 */
int getPropertyByRefNumber(int refNumber, const Property properties[], int propertyCount);

/**
 * @brief Updates a property's reference number.
 * @param properties Array of Property structures.
 * @param propertyCount The number of properties in the array.
 * @param index The index of the property to update.
 * @return true if the reference number is successfully updated, otherwise false.
 *
 * Special handling is required for refNumber as it must remain unique.
 */
bool updateRefNumber(Property properties[], int propertyCount, int index);

/**
 * @brief Updates a property's string field with new user input.
 * @param fieldPtr Pointer to the character array field to be updated.
 * @param maxSize The maximum size of the character array (including null terminator).
 * @param fieldName The name of the field being updated (for user prompts).
 * @return true if the field was updated, false if the user chose not to change it.
 *
 * This generic helper simplifies updating various text attributes of a property.
 */
bool updateStringField(char* fieldPtr, int maxSize, const char* fieldName);

/**
 * @brief Template function to update a property's numeric field with new user input.
 * @tparam T The numeric type of the field (e.g., int, double).
 * @param fieldPtr Pointer to the numeric field to be updated.
 * @param fieldName The name of the field being updated (for user prompts).
 * @return true if the field was updated, false if the user chose not to change it.
 *
 * Ensures valid numeric input and provides a consistent interface for updating numeric fields.
 */
template <typename T>
bool updateNumericField(T* fieldPtr, const char* fieldName) {
    std::cout << "Въведете нова стойност за " << fieldName << " (текуща: " << *fieldPtr << ", въведете -1 за запазване): ";
    T newValue;
    std::cin >> newValue;

    if (std::cin.fail()) {
        std::cout << "Невалиден вход. Запазена е текущата стойност.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    } else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (newValue != -1) { // Assume -1 is "no change" indicator
            *fieldPtr = newValue;
            return true;
        }
    }
    return false;
}

/**
 * @brief Updates a property's status.
 * @param propertyToUpdate Reference to the Property structure whose status is to be updated.
 * @return true if the status was updated, false if the user chose not to change it or input was invalid.
 *
 * Provides a guided process for changing the property's availability status.
 */
bool updateStatus(Property& propertyToUpdate);

#endif //UPDATE_H