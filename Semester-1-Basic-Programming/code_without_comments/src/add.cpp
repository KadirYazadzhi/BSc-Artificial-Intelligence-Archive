

#include <iostream>    
#include <limits>      
#include <cstring>     
#include <type_traits> 
#include <string>      
#include <algorithm>   

#include "add.h"       
#include "structs.h"   
#include "update.h"    
#include "file.h"      
#include "colors.h"    
#include "localization.h" 

using namespace std;


void sanitizeString(char* str) {
    int len = strlen(str);
    int k = 0; 
    for (int i = 0; i < len; i++) {
        if (str[i] != '|') { 
            str[k++] = str[i];
        }
    }
    str[k] = '\0'; 
}


void addSingleProperty(Property properties[], int& propertyCount) {
    
    if (isCapacityReached(propertyCount)) return;

    Property newProperty; 

    
    newProperty.refNumber = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_REF_NUMBER") + RESET).c_str());

    
    if (getPropertyByRefNumber(newProperty.refNumber, properties, propertyCount) != -1) {
        cout << RED << getTranslatedString("INVALID_DATA") << RESET << endl;
        cout << RED << getTranslatedString("ERROR_REF_NUMBER_EXISTS") << RESET << endl;
        cout << RED << getTranslatedString("ERROR_ADD_PROPERTY_FAILED") << RESET << endl;
        return; 
    }

    
    newProperty.price = getValidNumericInput<double>((CYAN + getTranslatedString("PROMPT_PRICE") + RESET).c_str());
    newProperty.totalArea = getValidNumericInput<double>((CYAN + getTranslatedString("PROMPT_TOTAL_AREA") + RESET).c_str());
    newProperty.rooms = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_ROOMS") + RESET).c_str());
    newProperty.floor = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_FLOOR") + RESET).c_str());

    
    
    getValidStringInput((CYAN + getTranslatedString("PROMPT_BROKER_NAME") + RESET).c_str(), newProperty.broker, sizeof(newProperty.broker));
    getValidStringInput((CYAN + getTranslatedString("PROMPT_PROPERTY_TYPE") + RESET).c_str(), newProperty.type, sizeof(newProperty.type));
    getValidStringInput((CYAN + getTranslatedString("PROMPT_PROPERTY_AREA") + RESET).c_str(), newProperty.area, sizeof(newProperty.area));
    getValidStringInput((CYAN + getTranslatedString("PROMPT_PROPERTY_EXPOSITION") + RESET).c_str(), newProperty.exposition, sizeof(newProperty.exposition));

    newProperty.status = AVAILABLE; 
    properties[propertyCount] = newProperty; 
    propertyCount++; 

    cout << endl;
    cout << GREEN << getTranslatedString("PROPERTY_ADDED_SUCCESS") << RESET << endl;
    syncDataToRecoveryFiles(properties, propertyCount); 
}


void addMultipleProperties(Property properties[], int& propertyCount) {
    
    int n = getValidNumericInput<int>((CYAN + getTranslatedString("PROMPT_NUM_PROPERTIES_TO_ADD") + RESET).c_str());

    
    if (propertyCount + n > MAX_PROPERTIES) {
        int availableSpace = MAX_PROPERTIES - propertyCount;
        cout << RED << getTranslatedString("ERROR_ADD_EXCEEDS_MAX_PART1") << RESET << endl;
        cout << YELLOW << getTranslatedString("ERROR_ADD_EXCEEDS_MAX_PART2") << " " << availableSpace << " " << getTranslatedString("ERROR_ADD_EXCEEDS_MAX_PART3") << RESET << endl;
        n = availableSpace; 
    }
    
    
    if (n <= 0) {
        isCapacityReached(propertyCount);
        return;
    }

    
    for (int i = 0; i < n; i++) {
        cout << YELLOW << "\n--- " << getTranslatedString("PROMPT_ENTERING_PROPERTY") << " #" << (i + 1) << " " << getTranslatedString("PROMPT_OF") << " " << n << " ---" << RESET << endl;
        addSingleProperty(properties, propertyCount); 
    }
}


bool isCapacityReached(int propertyCount) {
    if (propertyCount >= MAX_PROPERTIES) {
        cout << RED << getTranslatedString("ERROR_ADD_NOT_POSSIBLE") << RESET << endl;
        cout << RED << getTranslatedString("ERROR_MAX_CAPACITY_REACHED") << RESET << endl;
        return true;
    }
    return false;
}


void getValidStringInput(const char* prompt, char* buffer, int bufferSize) {
    cout << prompt; 
    cin.getline(buffer, bufferSize); 
    if (cin.fail()) { 
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << YELLOW << getTranslatedString("WARNING_INPUT_TRUNCATED") << RESET << endl; 
    }
    sanitizeString(buffer); 
}
