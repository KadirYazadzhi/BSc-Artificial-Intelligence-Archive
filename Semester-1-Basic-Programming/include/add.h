/**
 * @file add.h
 * @brief Declares functions related to adding new properties to the system.
 *
 * Includes functionality for adding single or multiple properties,
 * handling user input validation for various property attributes,
 * and checking system capacity limits.
 */

#ifndef ADD_H
#define ADD_H

#include "structs.h" // Necessary for Property type
#include <limits>    // Necessary for numeric_limits in getValidNumericInput
#include <iostream>  // Necessary for cin, cout in getValidNumericInput

/**
 * @brief Guides the user through adding a single new property to the system.
 * @param properties Array of Property structures where the new property will be added.
 * @param propertyCount Reference to an integer representing the current number of properties.
 *
 * Prompts the user for all necessary property details,
 * validates the input, and appends the property to the `properties` array.
 */
void addSingleProperty(Property properties[], int& propertyCount);

/**
 * @brief Allows the user to add multiple properties to the system in one session.
 * @param properties Array of Property structures where the new properties will be added.
 * @param propertyCount Reference to an integer representing the current number of properties.
 *
 * Repeatedly calls `addSingleProperty` until the user decides to stop
 * or the maximum capacity is reached.
 */
void addMultipleProperties(Property properties[], int& propertyCount);

/**
 * @brief Template function to obtain validated numeric input from the user.
 * @tparam T The expected numeric type (e.g., int, double).
 * @param prompt The message displayed to the user when requesting input.
 * @param errorMsg The error message displayed upon invalid input.
 * @return The validated numeric value entered by the user.
 *
 * Ensures robust input handling by repeatedly prompting the user
 * until a valid numeric value of the specified type is entered.
 */
template <typename T> T getValidNumericInput(const char* prompt, const char* errorMsg = "Невалиден вход. Опитайте отново: ") {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << errorMsg;
            std::cin.clear(); // Clear error flags
            // Ignore incorrect input line
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            // Clear all remaining characters in the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

/**
 * @brief Checks if the maximum property capacity has been reached.
 * @param propertyCount The current number of properties in the system.
 * @return true if capacity is reached, false otherwise.
 *
 * Prevents buffer overflow and ensures the application operates within defined limits.
 */
bool isCapacityReached(int propertyCount);

/**
 * @brief Sanitizes a C-style string by removing leading/trailing whitespace and replacing
 *        multiple internal spaces with a single space.
 * @param str The C-style string to sanitize.
 *
 * Helps standardize input strings for better data consistency and search functionality.
 */
void sanitizeString(char* str);

/**
 * @brief Prompts the user for string input and stores it in a buffer, with sanitization.
 * @param prompt The message displayed to the user when requesting input.
 * @param buffer The character buffer to store the input string.
 * @param bufferSize The maximum size of the buffer, including the null terminator.
 *
 * Combines user prompting with robust string input handling,
 * including sanitization to clean up the input.
 */
void getValidStringInput(const char* prompt, char* buffer, int bufferSize);

#endif //ADD_H