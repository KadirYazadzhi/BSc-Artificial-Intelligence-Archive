#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
#include "add.h"
#include "colors.h"
#include "localization.h"
#include "utils.h"

using namespace std;

template <typename T>
T getValidNumericInput(const char* prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << getTranslatedString("ERROR_INVALID_NUMERIC_INPUT") << RESET << endl;
    }
}

// Explicit instantiation for common types
template int getValidNumericInput<int>(const char*);
template double getValidNumericInput<double>(const char*);

void getValidStringInput(const char* prompt, char* buffer, size_t bufferSize) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        if (!input.empty()) {
            strncpy(buffer, input.c_str(), bufferSize - 1);
            buffer[bufferSize - 1] = '\0';
            sanitizeString(buffer);
            return;
        }
        cout << RED << getTranslatedString("ERROR_STRING_CANNOT_BE_EMPTY") << RESET << endl;
    }
}

void sanitizeString(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') str[i] = '-';
    }
}

void addSingleProperty(Node*& head) {
    Node* newNode = new Node();
    Property& prop = newNode->data;

    cout << CYAN << "\n--- " << getTranslatedString("ADD_PROPERTY_HEADER") << " ---" << RESET << endl;
    prop.refNumber = getValidNumericInput<int>(getTranslatedString("PROMPT_REF_NUMBER").c_str());
    getValidStringInput(getTranslatedString("PROMPT_BROKER_NAME").c_str(), prop.broker, sizeof(prop.broker));
    getValidStringInput(getTranslatedString("PROMPT_TYPE").c_str(), prop.type, sizeof(prop.type));
    getValidStringInput(getTranslatedString("PROMPT_AREA").c_str(), prop.area, sizeof(prop.area));
    getValidStringInput(getTranslatedString("PROMPT_EXPOSITION").c_str(), prop.exposition, sizeof(prop.exposition));
    prop.price = getValidNumericInput<double>(getTranslatedString("PROMPT_PRICE").c_str());
    prop.totalArea = getValidNumericInput<double>(getTranslatedString("PROMPT_TOTAL_AREA").c_str());
    prop.rooms = getValidNumericInput<int>(getTranslatedString("PROMPT_ROOMS").c_str());
    prop.floor = getValidNumericInput<int>(getTranslatedString("PROMPT_FLOOR").c_str());
    prop.status = AVAILABLE;

    newNode->next = head;
    head = newNode;

    cout << GREEN << getTranslatedString("SUCCESS_PROPERTY_ADDED") << RESET << endl;
}

void addMultipleProperties(Node*& head) {
    int n = getValidNumericInput<int>(getTranslatedString("PROMPT_NUMBER_OF_PROPERTIES").c_str());
    for (int i = 0; i < n; i++) {
        cout << YELLOW << "\n--- " << getTranslatedString("PROPERTY_HEADER") << " #" << i + 1 << " ---" << RESET << endl;
        addSingleProperty(head);
    }
}