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

    
    double maxArea = 0;
    Node* current = head;
    int count = 0;
    while (current != nullptr) {
        if (current->data.totalArea > maxArea) {
            maxArea = current->data.totalArea;
        }
        current = current->next;
    }

    
    current = head;
    while (current != nullptr) {
        if (current->data.totalArea == maxArea) {
            count++;
        }
        current = current->next;
    }

    if (count == 0) return;

    
    Property* arr = new Property[count];
    current = head;
    int idx = 0;
    while (current != nullptr) {
        if (current->data.totalArea == maxArea) {
            arr[idx++] = current->data;
        }
        current = current->next;
    }

    
    cout << YELLOW << getTranslatedString("REPORT_LARGEST_AREA_SORTING") << RESET << endl;
    selectionSort(arr, count);

    
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

    
    Property* arr = new Property[count];
    current = head;
    int idx = 0;
    while (current != nullptr) {
        if (current->data.status == SOLD) {
            arr[idx++] = current->data;
        }
        current = current->next;
    }

    
    cout << YELLOW << getTranslatedString("REPORT_SOLD_PROPERTIES_SORTING") << RESET << endl;
    mergeSort(arr, 0, count - 1);

    
    for (int i = 0; i < count; i++) {
        displayPropertyDetails(arr[i]);
    }

    delete[] arr;
}