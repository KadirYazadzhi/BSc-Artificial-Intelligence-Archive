#include <iostream>
#include "delete.h"
#include "add.h"
#include "colors.h"
#include "localization.h"

using namespace std;

void DeleteProperty(Node*& head) {
    if (head == nullptr) {
        cout << RED << getTranslatedString("ERROR_OPERATION_NOT_POSSIBLE_NO_PROPERTIES") << RESET << endl;
        return;
    }

    int refNumber = getValidNumericInput<int>(getTranslatedString("PROMPT_REF_NUMBER_TO_DELETE").c_str());

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.refNumber == refNumber) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            cout << GREEN << getTranslatedString("SUCCESS_PROPERTY_DELETED") << RESET << endl;
            return;
        }
        previous = current;
        current = current->next;
    }

    cout << RED << getTranslatedString("ERROR_PROPERTY_NOT_FOUND") << RESET << endl;
}

void DeleteAllProperties(Node*& head) {
    if (head == nullptr) return;

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << GREEN << getTranslatedString("SUCCESS_ALL_PROPERTIES_DELETED") << RESET << endl;
}