/**
 * @file localization.h
 * @brief Provides helper functions for managing application localization.
 *
 * Defines functions for loading translation strings from files, retrieving translated
 * text based on keys, and handling the initial language selection process by the user.
 */

#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <string> // Still needs std::string for some functions

// Defines the maximum number of translation entries
#define MAX_TRANSLATIONS 500
// Defines the maximum length of a translation key or value
#define MAX_TRANSLATION_STRING_LENGTH 256

/**
 * @brief Structure for storing a single translation entry.
 *
 * Contains the key (original string) and the value (translated string).
 */
struct TranslationEntry {
    char key[MAX_TRANSLATION_STRING_LENGTH];
    char value[MAX_TRANSLATION_STRING_LENGTH];
};

/**
 * @brief Global array storing translations.
 *
 * This array contains key-value entries where the key is the original string identifier
 * (e.g. "MENU_TITLE"), and the value is the translated string in the currently
 * selected language.
 */
extern TranslationEntry g_translations[MAX_TRANSLATIONS];
extern int g_translationCount; // The number of currently loaded translations
extern std::string currentLanguage; // The current language

/**
 * @brief Loads translations from a specified language file into the global translation map.
 * @param langCode String representing the language code (e.g., "en", "bg").
 *                  Expects a file named `lang/{langCode}.txt` to exist.
 */
void loadTranslations(const std::string& langCode);

/**
 * @brief Retrieves a translated string for a given key.
 * @param key The key (original string identifier) to look up in the translation map.
 * @return The translated string. If the key is not found, returns the key itself to indicate missing translation.
 */
std::string getTranslatedString(const std::string& key);

/**
 * @brief Guides the user in selecting the application language at startup.
 *
 * Displays available language options and prompts the user to
 * select one. Then calls `loadTranslations` with the selected language code.
 */
void selectLanguage();

#endif // LOCALIZATION_H