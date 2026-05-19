/**
 * @file utils.h
 * @brief Declares various utility functions used throughout the application.
 *
 * These functions provide common functionalities such as console manipulation,
 * directory management, user input handling, and displaying application banners.
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Clears the console screen.
 *
 * Uses system-specific commands to clear the terminal,
 * ensuring a cleaner user experience.
 */
void clearConsole();

/**
 * @brief Prints the application banner to the console.
 *
 * Called at application startup or
 * when returning to the main menu to display a welcome message or logo.
 */
void printBanner();

/**
 * @brief Ensures that the specified directory path exists. If not, attempts to create it.
 * @param path The path to the directory to check/create.
 *
 * This is critical when managing persistent storage, such as data files or logs,
 * ensuring the necessary file structure is available before operations.
 */
void ensureDirectoryExists(const char* path);

/**
 * @brief Prompts the user to enter a menu choice and validates the input.
 * @param min The minimum valid choice.
 * @param max The maximum valid choice.
 * @return The validated integer choice entered by the user.
 *
 * Improves user experience by ensuring menu selection input
 * falls within expected bounds and handling invalid entries gracefully.
 */
int getMenuChoice(int min, int max);

/**
 * @brief Prompts the user for a yes/no confirmation.
 * @param prompt The message displayed to the user for confirmation.
 * @return true if the user confirms (enters 'y' or 'Y'), otherwise false.
 *
 * Used for critical actions where explicit user consent is required before proceeding.
 */
bool getConfirmation(const char* prompt);

/**
 * @brief Compares two C-style strings without case sensitivity.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return true if strings are equal (case-insensitive), false otherwise.
 */
bool stringsEqualIgnoreCase(const char* s1, const char* s2);

#endif //UTILS_H