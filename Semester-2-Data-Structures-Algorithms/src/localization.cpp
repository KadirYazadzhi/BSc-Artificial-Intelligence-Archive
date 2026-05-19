/**
 * @file localization.cpp
 * @brief Implementation of localization helper functions managing language settings.
 *
 * This file provides the concrete implementation for loading translation files,
 * retrieving translated strings, and managing user language selection.
 * Uses a global map to store translation key-value pairs, allowing for
 * dynamic language switching and multi-language support.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits> // Necessary for numeric_limits
#include <string>   // Necessary for std::string
#include <cstring> // Necessary for strncpy and strcmp

#include "localization.h"
#include "utils.h" // Necessary for clearConsole and getConfirmation
#include "colors.h" // Necessary for color macros

// Defines the base directory using the preprocessor definition from CMake.
// This allows finding language files relative to the project root directory.
#ifdef PROJECT_ROOT_DIR
const std::string BASE_DIR = PROJECT_ROOT_DIR;
#else
// Fallback when PROJECT_ROOT_DIR is not defined (e.g., not compiled with CMake).
// In such cases, assumes the current working directory is the base directory.
const std::string BASE_DIR = ".";
#endif

// Global array storing translations.
// This array contains key-value entries where the key is the original string identifier
// (e.g. "MENU_TITLE"), and the value is the translated string in the currently
// selected language.
TranslationEntry g_translations[MAX_TRANSLATIONS];
int g_translationCount = 0; // The number of currently loaded translations

// Stores the current active language code (e.g. "en", "bg").
std::string currentLanguage = "bg"; // Default language is Bulgarian.

/**
 * @brief Loads translations from a specified language file into the global translation array.
 *
 * Clears any previously loaded translations and then parses a text file
 * located in the `lang/` directory. Expects each line in the file to be in
 * `KEY=VALUE` format. If unable to open the file, prints an error and
 * attempts to load the default Bulgarian language as a fallback to ensure basic
 * functionality.
 *
 * @param langCode String representing the language code (e.g., "en" for English, "bg" for Bulgarian).
 *                  Expects a file named `{langCode}.txt` to exist in the `lang/` subdirectory
 *                  of `BASE_DIR`.
 */
void loadTranslations(const std::string& langCode) {
    g_translationCount = 0; // Clears existing translations by resetting the counter.

    // Constructs the full path to the translation file.
    std::string filename = BASE_DIR + "/lang/" + langCode + ".txt"; // Uses absolute path
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << RED << "Error: Could not open translation file: / Грешка: Не може да се отвори файлът с преводи: " << filename << RESET << std::endl;
        // Fallback to default language Bulgarian if requested translation file is missing.
        // This prevents infinite recursion if bg.txt is also missing.
        if (langCode != "bg") {
            currentLanguage = "bg"; // Sets current language to default before loading.
            loadTranslations("bg");
        }
        return; // Exit after fallback attempt or if bg.txt is also missing.
    }

    std::string line;
    // Reads file line by line, parsing key-value pairs.
    while (std::getline(file, line) && g_translationCount < MAX_TRANSLATIONS) {
        size_t delimiterPos = line.find('='); // Finds the position of the '=' delimiter.
        if (delimiterPos != std::string::npos) {
            std::string key_str = line.substr(0, delimiterPos); // Extracts the key.
            std::string value_str = line.substr(delimiterPos + 1); // Extracts the value.

            // Copies key, ensuring null termination and preventing buffer overflow.
            strncpy(g_translations[g_translationCount].key, key_str.c_str(), MAX_TRANSLATION_STRING_LENGTH - 1);
            g_translations[g_translationCount].key[MAX_TRANSLATION_STRING_LENGTH - 1] = '\0';

            // Copies value, ensuring null termination and preventing buffer overflow.
            strncpy(g_translations[g_translationCount].value, value_str.c_str(), MAX_TRANSLATION_STRING_LENGTH - 1);
            g_translations[g_translationCount].value[MAX_TRANSLATION_STRING_LENGTH - 1] = '\0';
            
            g_translationCount++; // Increments loaded translation count.
        }
    }
    file.close(); // Closes translation file.
    currentLanguage = langCode; // Updates current language to the newly loaded one.
}

/**
 * @brief Retrieves a translated string for a given key from the global translation array.
 *
 * Iterates through the `g_translations` array searching for a matching key.
 * If the key is found, returns the corresponding translated string.
 * If the key is not found, prints a warning message to `cerr`
 * and returns the key itself. This fallback ensures the application
 * can still display some text even if a translation is missing, preventing crashes.
 *
 * @param key The key (original string identifier) to look up in the translation array.
 * @return The translated string if found, otherwise the key itself (along with a warning).
 */
std::string getTranslatedString(const std::string& key) {
    for (int i = 0; i < g_translationCount; ++i) {
        if (strcmp(g_translations[i].key, key.c_str()) == 0) {
            return std::string(g_translations[i].value);
        }
    }
    // Fallback: if key not found, return the key itself and log a warning.
    std::cerr << YELLOW << "Warning: Translation key '" << key << "' not found for language '" << currentLanguage << "'. / Предупреждение: Ключ за превод '" << key << "' не е намерен за език '" << currentLanguage << "'." << RESET << std::endl;
    return key;
}

/**
 * @brief Guides the user in selecting the application language at startup.
 *
 * Clears the console, displays a list of available languages (English and Bulgarian),
 * and prompts the user to make a choice. Includes input validation to ensure the user
 * enters a valid option (1 or 2). Once a valid choice is made, calls `loadTranslations`
 * to load the strings of the selected language and confirms the language setting to the user.
 */
void selectLanguage() {
    clearConsole(); // Clears console for a clean language selection interface.
    std::cout << "Select Language / Изберете език:" << std::endl;
    std::cout << "  1. English (en) / Английски (en)" << std::endl;
    std::cout << "  2. Bulgarian (bg) / Български (bg)" << std::endl;
    std::cout << "Enter your choice / Въведете вашия избор: ";

    int choice;
    // Loop to continuously prompt for input until a valid choice (1 or 2) is entered.
    while (!(std::cin >> choice) || (choice < 1 || choice > 2)) {
        std::cout << RED << "Invalid choice. Please enter 1 or 2. / Невалиден избор. Моля, въведете 1 или 2." << RESET << std::endl;
        std::cin.clear(); // Clears cin error flags.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards invalid input.
        std::cout << "Enter your choice / Въведете вашия избор: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards remaining newline character.

    // Loads translations based on valid user choice.
    if (choice == 1) {
        loadTranslations("en");
    } else { // choice == 2
        loadTranslations("bg");
    }
    // Informs the user that language has been successfully set, using the newly loaded translations.
    std::cout << GREEN << getTranslatedString("LANGUAGE_SET_SUCCESS") << RESET << std::endl;
}
