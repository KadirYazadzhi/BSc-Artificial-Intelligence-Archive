#include <iostream>
#include <cstdlib>
#include "menu.h"
#include "utils.h"
#include "add.h"
#include "display.h"
#include "delete.h"
#include "reports.h"
#include "search.h"
#include "sort.h"
#include "colors.h"
#include "localization.h"

using namespace std;

void mainMenu(Node*& head) {
    while (true) {
        clearConsole();
        cout << CYAN << getTranslatedString("MAIN_MENU_TITLE") << RESET << endl;
        cout << getTranslatedString("MAIN_MENU_ADD_PROPERTY") << endl;
        cout << getTranslatedString("MAIN_MENU_DELETE_PROPERTY") << endl;
        cout << getTranslatedString("MAIN_MENU_DISPLAY_PROPERTIES") << endl;
        cout << getTranslatedString("MAIN_MENU_SEARCH") << endl;
        cout << getTranslatedString("MAIN_MENU_SORT") << endl;
        cout << getTranslatedString("MAIN_MENU_REPORTS") << endl;
        cout << getTranslatedString("MAIN_MENU_EXIT") << endl;

        int choice = getMenuChoice(0, 6);

        switch (choice) {
            case 0:
                cout << YELLOW << getTranslatedString("THANK_YOU_MESSAGE") << RESET << endl;
                return;
            case 1: addPropertyMenu(head); break;
            case 2: deletePropertyMenu(head); break;
            case 3: displayMenu(head); break;
            case 4: searchByRefNumberBinary(head); break; 
            case 5: sortMenu(head); break;
            case 6: reportsMenu(head); break;
            default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break;
        }
        if (choice != 0) {
            cout << "\n" << getTranslatedString("PROMPT_PRESS_ENTER_TO_CONTINUE");
            cin.get();
        }
    }
}

void addPropertyMenu(Node*& head) {
    clearConsole();
    cout << CYAN << getTranslatedString("ADD_MENU_TITLE") << RESET << endl;
    cout << getTranslatedString("ADD_MENU_SINGLE_PROPERTY") << endl;
    cout << getTranslatedString("ADD_MENU_MULTIPLE_PROPERTIES") << endl;
    cout << getTranslatedString("ADD_MENU_BACK") << endl;

    int choice = getMenuChoice(0, 2);
    switch (choice) {
        case 1: addSingleProperty(head); break;
        case 2: addMultipleProperties(head); break;
    }
}

void deletePropertyMenu(Node*& head) {
    clearConsole();
    cout << CYAN << getTranslatedString("DELETE_MENU_TITLE") << RESET << endl;
    cout << getTranslatedString("DELETE_MENU_SINGLE_PROPERTY") << endl;
    cout << getTranslatedString("DELETE_MENU_ALL_PROPERTIES") << endl;
    cout << getTranslatedString("ADD_MENU_BACK") << endl;

    int choice = getMenuChoice(0, 2);
    switch (choice) {
        case 1: DeleteProperty(head); break;
        case 2: DeleteAllProperties(head); break;
    }
}

void displayMenu(Node* head) {
    clearConsole();
    cout << CYAN << getTranslatedString("DISPLAY_MENU_TITLE") << RESET << endl;
    cout << getTranslatedString("DISPLAY_MENU_ALL_PROPERTIES") << endl;
    cout << getTranslatedString("DISPLAY_MENU_SOLD_PROPERTIES") << endl;
    cout << getTranslatedString("DISPLAY_MENU_LARGEST_PROPERTIES") << endl;
    cout << getTranslatedString("ADD_MENU_BACK") << endl;

    int choice = getMenuChoice(0, 3);
    switch (choice) {
        case 1: displayAllProperties(head); break;
        case 2: displaySoldProperties(head); break;
        case 3: displayLargestProperties(head); break;
    }
}

void sortMenu(Node* head) {
    clearConsole();
    cout << CYAN << getTranslatedString("SORT_MENU_TITLE") << RESET << endl;
    cout << getTranslatedString("SORT_MENU_FIRST_TEN_ARRAY") << endl;
    cout << getTranslatedString("SORT_MENU_LINKED_LIST_BUBBLE") << endl;
    cout << getTranslatedString("ADD_MENU_BACK") << endl;

    int choice = getMenuChoice(0, 2);
    switch (choice) {
        case 1: sortFirstTenInArray(head); break;
        case 2: sortLinkedList(head); break;
    }
}

void reportsMenu(Node* head) {
    clearConsole();
    cout << CYAN << getTranslatedString("REPORTS_MENU_TITLE") << RESET << endl;
    cout << getTranslatedString("REPORTS_MENU_LARGEST_AREA_SELECTION_SORT") << endl;
    cout << getTranslatedString("REPORTS_MENU_SOLD_PROPERTIES_MERGE_SORT") << endl;
    cout << getTranslatedString("ADD_MENU_BACK") << endl;

    int choice = getMenuChoice(0, 2);
    switch (choice) {
        case 1: reportLargestAreaSorted(head); break;
        case 2: reportSoldPropertiesSorted(head); break;
    }
}