

#include <iostream>    
#include <cctype>      
#include <limits>      
#include <string>      

#include "delete.h"    
#include "structs.h"   
#include "update.h"    
#include "file.h"      
#include "colors.h"    
#include "add.h"       
#include "utils.h"     
#include "localization.h" 

using namespace std;


void DeleteProperty(Property properties[], int& propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_TO_DELETE") << RESET << endl;
        return;
    }

    
    int refNumber = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_REF_NUMBER_TO_DELETE") + RESET).c_str());

    
    int index = getPropertyByRefNumber(refNumber, properties, propertyCount);
    if (index == -1) {
        cout << RED << getTranslatedString("ERROR_PROPERTY_NOT_FOUND_REF") << RESET << endl;
        return;
    }

    
    if (!getConfirmation((getTranslatedString("CONFIRM_DELETE_PROPERTY_PART1") + " - " + to_string(refNumber) + "? [y/n]: ").c_str())) {
        cout << YELLOW << getTranslatedString("DELETE_CANCELLED") << RESET << endl;
        return;
    }

    
    for (int i = index; i < propertyCount - 1; i++) {
        properties[i] = properties[i + 1];
    }

    propertyCount--; 

    cout << GREEN << getTranslatedString("PROPERTY_DELETED_SUCCESS_PART1") << " " << refNumber << " " << getTranslatedString("PROPERTY_DELETED_SUCCESS_PART2") << RESET << endl;
    syncDataToRecoveryFiles(properties, propertyCount); 
}


void DeleteAllProperties(Property properties[], int& propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_TO_DELETE") << RESET << endl;
        return;
    }

    
    if (!getConfirmation(getTranslatedString("CONFIRM_DELETE_ALL_PROPERTIES").c_str())) {
        cout << YELLOW << getTranslatedString("DELETE_ALL_CANCELLED") << RESET << endl;
        return;
    }

    propertyCount = 0; 

    cout << GREEN << getTranslatedString("ALL_PROPERTIES_DELETED_SUCCESS") << RESET << endl;
    syncDataToRecoveryFiles(properties, propertyCount); 
}