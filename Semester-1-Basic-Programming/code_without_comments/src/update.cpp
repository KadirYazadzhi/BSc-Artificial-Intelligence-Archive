

#include <iostream>    
#include <cstring>     
#include <limits>      
#include <string>      
#include <iomanip>     

#include "update.h"    
#include "structs.h"   
#include "file.h"      
#include "colors.h"    
#include "add.h"       
#include "localization.h" 

using namespace std;


void updateProperty(Property properties[], int& propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }
    
    
    int refNumber = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_REF_NUMBER_TO_UPDATE") + RESET).c_str());
    
    int index = getPropertyByRefNumber(refNumber, properties, propertyCount);

    if (index == -1) {
        cout << RED << getTranslatedString("ERROR_PROPERTY_NOT_FOUND_REF") << " - " << refNumber << "." << RESET << endl;
        return;
    }

    
    if (properties[index].status == SOLD) {
        cout << RED << getTranslatedString("ERROR_SOLD_PROPERTY_CANNOT_BE_EDITED") << RESET << endl;
        return;
    }

    
    cout << CYAN << getTranslatedString("UPDATE_MENU_CHOOSE_FIELD") << RESET << endl;
    cout << left; 
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_REF_NUMBER") << getTranslatedString("UPDATE_MENU_PRICE") << endl;
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_BROKER") << getTranslatedString("UPDATE_MENU_TOTAL_AREA") << endl;
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_TYPE") << getTranslatedString("UPDATE_MENU_ROOMS") << endl;
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_AREA") << getTranslatedString("UPDATE_MENU_FLOOR") << endl;
    cout << "  " << setw(15) << getTranslatedString("UPDATE_MENU_EXPOSITION") << getTranslatedString("UPDATE_MENU_STATUS") << endl;
    cout << "  " << getTranslatedString("ADD_MENU_BACK") << endl; 

    
    int choice = getValidNumericInput<int>((CYAN + getTranslatedString("ENTER_YOUR_CHOICE") + RESET).c_str());

    bool updateMade = false; 
    switch (choice) {
        case 1: updateMade = updateRefNumber(properties, propertyCount, index); break;
        case 2: updateMade = updateStringField(properties[index].broker, 50, getTranslatedString("BROKER_FIELD_NAME").c_str()); break;
        case 3: updateMade = updateStringField(properties[index].type, 50, getTranslatedString("TYPE_FIELD_NAME").c_str()); break;
        case 4: updateMade = updateStringField(properties[index].area, 50, getTranslatedString("AREA_FIELD_NAME").c_str()); break;
        case 5: updateMade = updateStringField(properties[index].exposition, 20, getTranslatedString("EXPOSITION_FIELD_NAME").c_str()); break;
        case 6: updateMade = updateNumericField(&properties[index].price, getTranslatedString("PRICE_FIELD_NAME").c_str()); break;
        case 7: updateMade = updateNumericField(&properties[index].totalArea, getTranslatedString("TOTAL_AREA_FIELD_NAME").c_str()); break;
        case 8: updateMade = updateNumericField(&properties[index].rooms, getTranslatedString("ROOMS_FIELD_NAME").c_str()); break;
        case 9: updateMade = updateNumericField(&properties[index].floor, getTranslatedString("FLOOR_FIELD_NAME").c_str()); break;
        case 10: updateMade = updateStatus(properties[index]); break;
        case 0: return; 
        default: cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl; break;
    }

    if (updateMade) {
        cout << GREEN << getTranslatedString("PROPERTY_DATA_UPDATED_SUCCESS") << RESET << endl;
        syncDataToRecoveryFiles(properties, propertyCount); 
    }
}


int getPropertyByRefNumber(int refNumber, const Property properties[], int propertyCount) {
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].refNumber == refNumber) return i;
    }
    return -1; 
}


bool updateRefNumber(Property properties[], int propertyCount, int index) {
    
    int newRefNumber = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_NEW_REF_NUMBER") + RESET).c_str());

    
    if (properties[index].refNumber == newRefNumber) {
         cout << YELLOW << getTranslatedString("WARNING_VALUE_IDENTICAL") << RESET << endl;
        return false;
    }

    
    if (getPropertyByRefNumber(newRefNumber, properties, propertyCount) != -1) {
        cout << RED << getTranslatedString("ERROR_INVALID_OPERATION_REF_EXISTS") << RESET << endl;
        return false;
    }

    properties[index].refNumber = newRefNumber; 
    return true;
}


bool updateStringField(char* fieldPtr, int maxSize, const char* fieldName) {
    char newValue[MAX_STRING_SIZE]; 
    
    string prompt = string(CYAN) + getTranslatedString("PROMPT_NEW_VALUE_FOR") + " " + fieldName + " (" + getTranslatedString("UP_TO") + " " + to_string(maxSize - 1) + " " + getTranslatedString("CHARACTERS") + "): " + RESET;
    
    getValidStringInput(prompt.c_str(), newValue, sizeof(newValue));

    
    if (strcmp(fieldPtr, newValue) == 0) {
        cout << YELLOW << getTranslatedString("WARNING_VALUE_IDENTICAL") << RESET << endl;
        return false;
    }

    
    strncpy(fieldPtr, newValue, maxSize - 1);
    fieldPtr[maxSize - 1] = '\0'; 
    return true;
}



bool updateStatus(Property& propertyToUpdate) {
    Status oldStatus = propertyToUpdate.status; 

    
    cout << CYAN << getTranslatedString("PROMPT_SELECT_NEW_STATUS") << RESET << endl;
    cout << left;
    cout << "  " << setw(15) << getTranslatedString("STATUS_AVAILABLE") << endl;
    cout << "  " << setw(15) << getTranslatedString("STATUS_SOLD") << endl;
    cout << "  " << setw(15) << getTranslatedString("STATUS_RESERVED") << endl;
    
    int choice;
    
    while (true) {
        choice = getValidNumericInput<int>((CYAN + getTranslatedString("ENTER_YOUR_CHOICE") + RESET).c_str());
        if (choice >= 1 && choice <= 3) break; 
        cout << RED << getTranslatedString("ERROR_INVALID_STATUS_CHOICE") << RESET << endl;
    }

    Status newStatus;
    switch (choice) {
        case 1: newStatus = AVAILABLE; break;
        case 2: newStatus = SOLD; break;
        case 3: newStatus = RESERVED; break;
        default: return false; 
    }

    
    if (oldStatus == newStatus) {
        cout << YELLOW << getTranslatedString("WARNING_STATUS_IDENTICAL") << RESET << endl;
        return false;
    }

    
    if (oldStatus == AVAILABLE && newStatus == RESERVED) {
        propertyToUpdate.price *= 0.8; 
        cout << YELLOW << getTranslatedString("WARNING_PRICE_REDUCED_RESERVED") << RESET << endl;
    }

    propertyToUpdate.status = newStatus; 
    return true;
}
