#include <iostream>
#include "search.h"
#include "display.h"
#include "add.h"
#include "colors.h"
#include "localization.h"

using namespace std;

int binarySearchRecursive(Property arr[], int low, int high, int key) {
    if (high >= low) {
        int mid = low + (high - low) / 2;
        if (arr[mid].refNumber == key) return mid;
        if (arr[mid].refNumber > key) return binarySearchRecursive(arr, low, mid - 1, key);
        return binarySearchRecursive(arr, mid + 1, high, key);
    }
    return -1;
}

void searchByRefNumberBinary(Node* head) {
    if (head == nullptr) {
        cout << RED << getTranslatedString("ERROR_OPERATION_NOT_POSSIBLE_NO_PROPERTIES") << RESET << endl;
        return;
    }

    // Count elements for array allocation
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    // Standard dynamic array (no vector)
    Property* props = new Property[count];
    Node* current = head;
    for (int i = 0; i < count; i++) {
        props[i] = current->data;
        current = current->next;
    }

    // Simple Selection Sort by refNumber (no STL sort)
    selectionSortByRefNumber(props, count);

    int key = getValidNumericInput<int>(getTranslatedString("PROMPT_REF_NUMBER").c_str());
    int result = binarySearchRecursive(props, 0, count - 1, key);

    if (result != -1) {
        cout << GREEN << getTranslatedString("SUCCESS_PROPERTY_FOUND") << RESET << endl;
        displayPropertyDetails(props[result]);
    } else {
        cout << RED << getTranslatedString("ERROR_PROPERTY_NOT_FOUND") << RESET << endl;
    }

    delete[] props;
}
  if (result != -1) {
        cout << GREEN << getTranslatedString("SUCCESS_PROPERTY_FOUND") << RESET << endl;
        displayPropertyDetails(props[result]);
    } else {
        cout << RED << getTranslatedString("ERROR_PROPERTY_NOT_FOUND") << RESET << endl;
    }

    delete[] props;
}
