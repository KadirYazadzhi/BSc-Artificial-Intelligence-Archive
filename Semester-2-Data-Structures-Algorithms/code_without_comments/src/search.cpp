#include <iostream>
#include <vector>
#include <algorithm>
#include "search.h"
#include "display.h"
#include "add.h"
#include "colors.h"
#include "localization.h"

using namespace std;


bool compareByRefNumber(const Property& a, const Property& b) {
    return a.refNumber < b.refNumber;
}

int binarySearchRecursive(const vector<Property>& arr, int low, int high, int key) {
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

    
    vector<Property> props;
    Node* current = head;
    while (current != nullptr) {
        props.push_back(current->data);
        current = current->next;
    }

    
    sort(props.begin(), props.end(), compareByRefNumber);

    int key = getValidNumericInput<int>(getTranslatedString("PROMPT_REF_NUMBER").c_str());
    int result = binarySearchRecursive(props, 0, props.size() - 1, key);

    if (result != -1) {
        cout << GREEN << getTranslatedString("SUCCESS_PROPERTY_FOUND") << RESET << endl;
        displayPropertyDetails(props[result]);
    } else {
        cout << RED << getTranslatedString("ERROR_PROPERTY_NOT_FOUND") << RESET << endl;
    }
}