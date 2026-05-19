#include <iostream>
#include "reports.h"
#include "sort.h"
#include "display.h"
#include "colors.h"
#include "localization.h"

using namespace std;

void reportLargestAreaSorted(Node* head) {
    if (head == nullptr) {
        cout << RED << getTranslatedString("ERROR_OPERATION_NOT_POSSIBLE_NO_PROPERTIES") << RESET << endl;
        return;
    }

    // Pass 1: Find max area
    double maxArea = 0;
    Node* current = head;
    int count = 0;
    while (current != nullptr) {
        if (current->data.totalArea > maxArea) {
            maxArea = current->data.totalArea;
        }
        current = current->next;
    }

    // Pass 2: Count matches
    current = head;
    while (current != nullptr) {
        if (current->data.totalArea == maxArea) {
            count++;
        }
        current = current->next;
    }

    if (count == 0) return;

    // Save to array
    Property* arr = new Property[count];
    current = head;
    int idx = 0;
    while (current != nullptr) {
        if (current->data.totalArea == maxArea) {
            arr[idx++] = current->data;
        }
        current = current->next;
    }

    // Sort using Selection Sort (Criterion a)
    cout << YELLOW << getTranslatedString("REPORT_LARGEST_AREA_SORTING") << RESET << endl;
    selectionSort(arr, count);

    // Display
    for (int i = 0; i < count; i++) {
        displayPropertyDetails(arr[i]);
    }

    delete[] arr;
}

void reportSoldPropertiesSorted(Node* head) {
    if (head == nullptr) {
        cout << RED << getTranslatedString("ERROR_OPERATION_NOT_POSSIBLE_NO_PROPERTIES") << RESET << endl;
        return;
    }

    // Pass 1: Count sold
    Node* current = head;
    int count = 0;
    while (current != nullptr) {
        if (current->data.status == SOLD) {
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        cout << YELLOW << getTranslatedString("NO_SOLD_PROPERTIES_CURRENTLY") << RESET << endl;
        return;
    }

    // Save to array
    Property* arr = new Property[count];
    current = head;
    int idx = 0;
    while (current != nullptr) {
        if (current->data.status == SOLD) {
            arr[idx++] = current->data;
        }
        current = current->next;
    }

    // Sort using Merge Sort (Criterion b)
    cout << YELLOW << getTranslatedString("REPORT_SOLD_PROPERTIES_SORTING") << RESET << endl;
    mergeSort(arr, 0, count - 1);

    // Display
    for (int i = 0; i < count; i++) {
        displayPropertyDetails(arr[i]);
    }

    delete[] arr;
}