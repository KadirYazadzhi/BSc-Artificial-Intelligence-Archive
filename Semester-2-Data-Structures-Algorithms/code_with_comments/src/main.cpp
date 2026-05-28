/**
 * @file main.cpp
 * @brief Main entry point for the Real Estate Agency Management System.
 */

#include "structs.h"
#include "utils.h"
#include "menu.h"
#include "localization.h"
#include "test_data.h"

/**
 * @brief Application entry point.
 */
int main() {
    Node* head = nullptr; // Initialize the linked list head to nullptr.

    // Loads default language translations (Bulgarian).
    loadTranslations("bg");

    // Displays the application ASCII art banner.
    printBanner();

    // Prompts the user to select their preferred language.
    selectLanguage();

    // In the new version, file loading is dropped.
    // We can still generate test data if the list is empty.
    if (head == nullptr) {
        if (getConfirmation(getTranslatedString("GENERATE_TEST_DATA_PROMPT").c_str())) {
            generateTestProperties(head);
        }
    }

    // Starts the main menu loop, passing the head of the linked list.
    mainMenu(head);

    // Basic cleanup (could be more thorough with a dedicated function)
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}