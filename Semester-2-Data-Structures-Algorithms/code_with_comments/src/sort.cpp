#include <iostream>
#include "sort.h"
#include "display.h"
#include "colors.h"
#include "localization.h"

using namespace std;

void sortFirstTenInArray(Node* head) {
    if (head == nullptr) {
        cout << RED << getTranslatedString("ERROR_OPERATION_NOT_POSSIBLE_NO_PROPERTIES") << RESET << endl;
        return;
    }

    Property arr[10];
    int count = 0;
    Node* current = head;
    while (current != nullptr && count < 10) {
        arr[count++] = current->data;
        current = current->next;
    }

    cout << YELLOW << getTranslatedString("SORTING_FIRST_TEN_MESSAGE") << RESET << endl;
    quickSort(arr, 0, count - 1);

    for (int i = 0; i < count; i++) {
        cout << CYAN << "--- #" << i + 1 << " ---" << RESET << endl;
        displayPropertyDetails(arr[i]);
    }
}

void sortLinkedList(Node* head) {
    if (head == nullptr) {
        cout << RED << getTranslatedString("ERROR_OPERATION_NOT_POSSIBLE_NO_PROPERTIES") << RESET << endl;
        return;
    }

    cout << YELLOW << getTranslatedString("SORTING_LINKED_LIST_MESSAGE") << RESET << endl;
    bubbleSort(head);
    cout << GREEN << getTranslatedString("SUCCESS_PROPERTIES_SORTED") << RESET << endl;
}