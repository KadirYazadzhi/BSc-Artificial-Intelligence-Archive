#include <iostream>
#include <iomanip>
#include "display.h"
#include "colors.h"
#include "localization.h"

using namespace std;

bool isPropertiesEmpty(Node* head) {
    if (head == nullptr) {
        cout << RED << getTranslatedString("ERROR_OPERATION_NOT_POSSIBLE_NO_PROPERTIES") << RESET << endl;
        return true;
    }
    return false;
}

void displayPropertyDetails(const Property& prop) {
    cout << left;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_REF_NUMBER") << prop.refNumber << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_BROKER_NAME") << prop.broker << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_TYPE") << prop.type << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_AREA") << prop.area << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_EXPOSITION") << prop.exposition << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_PRICE") << fixed << setprecision(2) << prop.price << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_TOTAL_AREA") << fixed << setprecision(2) << prop.totalArea << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_ROOMS") << prop.rooms << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_FLOOR") << prop.floor << endl;
    cout << "  " << setw(18) << getTranslatedString("PROPERTY_DETAILS_STATUS") << getStatusString(prop.status) << endl;
    cout << endl;
}

void displayAllProperties(Node* head) {
    if (isPropertiesEmpty(head)) return;

    Node* current = head;
    int count = 1;
    while (current != nullptr) {
        cout << YELLOW << "--- " << getTranslatedString("PROPERTY_HEADER") << " #" << count++ << " ---" << RESET << endl;
        displayPropertyDetails(current->data);
        current = current->next;
    }
}

void displaySoldProperties(Node* head) {
    if (isPropertiesEmpty(head)) return;

    bool isFound = false;
    Node* current = head;
    int count = 1;
    while (current != nullptr) {
        if (current->data.status == SOLD) {
            if (!isFound) {
                cout << YELLOW << "--- " << getTranslatedString("SOLD_PROPERTIES_HEADER") << " ---" << RESET << endl;
                isFound = true;
            }
            cout << YELLOW << "#" << count++ << RESET << endl;
            displayPropertyDetails(current->data);
        }
        current = current->next;
    }

    if (!isFound) {
        cout << YELLOW << getTranslatedString("NO_SOLD_PROPERTIES_CURRENTLY") << RESET << endl;
    }
}

void displayLargestProperties(Node* head) {
    if (isPropertiesEmpty(head)) return;

    double maxArea = 0.0;
    Node* current = head;
    while (current != nullptr) {
        if (current->data.totalArea > maxArea) {
            maxArea = current->data.totalArea;
        }
        current = current->next;
    }

    if (maxArea == 0.0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_WITH_AREA_GREATER_THAN_ZERO") << RESET << endl;
        return;
    }

    cout << YELLOW << "--- " << getTranslatedString("LARGEST_PROPERTIES_HEADER") << " (" << fixed << setprecision(2) << maxArea << " " << getTranslatedString("SQ_M") << ") ---" << RESET << endl;
    current = head;
    int count = 1;
    while (current != nullptr) {
        if (current->data.totalArea == maxArea) {
            cout << YELLOW << "#" << count++ << RESET << endl;
            displayPropertyDetails(current->data);
        }
        current = current->next;
    }
}