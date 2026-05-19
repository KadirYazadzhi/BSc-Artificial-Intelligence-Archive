/**
 * @file structs.cpp
 * @brief Implementation of my helper functions and global variables related to core data structures.
 *
 * This file primarily implements the logic for converting the `Status` enumeration
 * into localized string representations, utilizing the localization module
 * to support multiple languages for user-facing status messages.
 */

#include "structs.h" // Necessary for Property structure
#include "localization.h" // Necessary for access to translation functions

/**
 * @brief Converts a Status enum value to its corresponding localized string representation.
 *
 * This function is key for me to display user-friendly status messages in the
 * currently selected language. I use `getTranslatedString` from the
 * localization module to retrieve the appropriate string based on predefined keys.
 * By this approach, I centralize all language-specific text, making my application
 * easily localizable without changing core logic.
 *
 * @param status The Status enumeration value to convert (SOLD, RESERVED, AVAILABLE).
 * @return Localized string representing the status.
 *         Returns a localized "unknown" status string if an unhandled status is encountered.
 */
std::string getStatusString(enum Status status) {
    switch (status) {
        case SOLD:
            // Return translated string for "SOLD" status.
            return getTranslatedString("STATUS_SOLD_TEXT");
        case RESERVED:
            // Return translated string for "RESERVED" status.
            return getTranslatedString("STATUS_RESERVED_TEXT");
        case AVAILABLE:
            // Return translated string for "AVAILABLE" status.
            return getTranslatedString("STATUS_AVAILABLE_TEXT");
        default:
            // Fallback for any unhandled status, return localized "unknown" text.
            return getTranslatedString("STATUS_UNKNOWN_TEXT");
    }
}
