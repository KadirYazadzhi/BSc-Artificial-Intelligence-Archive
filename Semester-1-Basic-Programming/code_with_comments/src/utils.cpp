/**
 * @file utils.cpp
 * @brief Implementation of various utility functions for console manipulation,
 *        user interaction, and system checks.
 *
 * Here specific implementations are provided for functions declared in `utils.h`,
 * including clearing the console, displaying banners, ensuring directory existence,
 * processing validated menu choices, and obtaining user confirmations.
 */

#include <iostream>
#include <limits>      // Necessary for numeric_limits
#include <string>      // Necessary for string
#include <cctype>      // Necessary for tolower
#include <cstdlib>     // Necessary for system
#include "utils.h"
#include "colors.h"    // Necessary for CYAN and RESET
#include "localization.h" // Necessary for localization functions like getTranslatedString

using namespace std;

/**
 * @brief Clears the console screen using ANSI escape codes.
 *
 * Sends specific escape sequences to the terminal to wipe
 * its content and move the cursor to the top-left corner.
 * This ensures a clean interface for menu navigation and output display.
 */
void clearConsole() {
  // \033[2J clears the entire screen.
  // \033[1;1H moves the cursor to row 1, column 1.
  cout << "\033[2J\033[1;1H";
}

/**
 * @brief Displays the application ASCII art banner.
 *
 * Prints predefined ASCII art text to the console,
 * serving as a welcome message or application branding at startup
 * or return to main menus.
 */
void printBanner() {
  cout << R"(
██████╗ ███████╗ █████╗ ██╗         ███████╗███████╗████████╗ █████╗ ████████╗███████╗     █████╗  ██████╗ ███████╗███╗   ██╗ ██████╗██╗   ██╗
██╔══██╗██╔════╝██╔══██╗██║         ██╔════╝██╔════╝╚══██╔══╝██╔══██╗╚══██╔╝╝ ██╔════╝    ██╔══██╗██╔════╝ ██╔════╝████╗  ██║██╔════╝╚██╗ ██╔╝
██████╔╝█████╗  ███████║██║         █████╗  ███████╗   ██║   ███████║   ██║   █████╗      ███████║██║  ███╗█████╗  ██╔██╗ ██║██║      ╚████╔╝
██╔══██╗██╔══╝  ██╔══██║██║         ██╔══╝  ╚════██║   ██║   ██╔══██║   ██║   ██╔══╝      ██╔══██║██║   ██║██╔══╝  ██║╚██╗██║██║       ╚██╔╝
██║  ██║███████╗██║  ██║███████╗    ███████╗███████║   ██║   ██║  ██║   ██║   ███████╗    ██║  ██║╚██████╔╝███████╗██║ ╚████║╚██████╗   ██║
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝  ╚═╝
        Информационна система 'Агенция за недвижими имоти'                                                     realestateagency - @kadir_
  )"
  << endl;
}

/**
 * @brief Ensures that the specified directory path exists, creating it if necessary.
 *
 * Uses the `mkdir -p` shell command to create directories.
 * This is vital for setting up necessary file structure for data storage
 * (e.g., recovery files, logs) before attempting to write to them.
 * `mkdir -p` ensures parent directories are also created if missing,
 * and doesn't return an error if the directory already exists.
 *
 * @param path C-style string representing the path to the directory to check/create.
 */
void ensureDirectoryExists(const char* path) {
    string command = "mkdir -p "; // The `-p` flag creates parent directories as needed
    command += path;
    system(command.c_str()); // Executes the shell command
}

/**
 * @brief Prompts the user for a menu choice and validates their input.
 *
 * Ensures that user input for menu selection is a valid integer
 * within a specific range (`min` and `max`). Handles non-integer inputs
 * and out-of-range inputs by clearing `cin` error state and discarding
 * invalid characters, then returning -1 to indicate invalid choice.
 * Localizes the selection prompt using `getTranslatedString`.
 *
 * @param min The minimum valid integer choice.
 * @param max The maximum valid integer choice.
 * @return The validated integer choice entered by the user, or -1 if input is invalid.
 */
int getMenuChoice(int min, int max) {
    int choice;
    cout << CYAN << getTranslatedString("ENTER_YOUR_CHOICE") << RESET; // Localized prompt

    // Checks if input stream failed (e.g. non-integer input)
    if (!cin) {
        cin.clear(); // Clears error flags
        choice = -1; // Assigns invalid choice to trigger error handling later
    }
    // Discards the rest of the input line to prevent issues with subsequent inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Validates if choice is within acceptable range
    if (choice < min || choice > max) {
        return -1; // Indicates invalid choice
    }

    return choice;
}

/**
 * @brief Prompts the user for confirmation with "yes" or "no".
 *
 * Presents a localized prompt to the user, expecting a single
 * character input. Converts input to lowercase and returns true if
 * input is 'y' (for yes), and false otherwise. Used for critical
 * operations where user consent is needed, such as deleting data or overwriting files.
 *
 * @param prompt C-style string representing the prompt displayed to the user.
 * @return true if user enters 'y' or 'Y', otherwise false.
 */
bool getConfirmation(const char* prompt) {
    char option;
    cout << YELLOW << prompt << RESET; // Shows prompt with yellow color for emphasis
    cin >> option;

    // Checks if input stream failed (e.g. no input)
    if (!cin) {
        cin.clear(); // Clears error flags
    }

    // Discards the rest of the input line
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Converts to lowercase and checks if 'y'
    return (tolower(option) == 'y');
}

/**
 * @brief Compares two C-style strings without case sensitivity.
 *
 * Iterates through both strings simultaneously, converting each character to lowercase
 * before comparison. This ensures that "Sofia" and "sofia" are treated as identical.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return true if strings are equal, false otherwise.
 */
bool stringsEqualIgnoreCase(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return false;
        }
        s1++;
        s2++;
    }
    // Check if both strings ended at the same time (i.e., have equal length)
    return (*s1 == *s2);
}
