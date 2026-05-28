

#ifndef UPDATE_H
#define UPDATE_H

#include "structs.h" 
#include <iostream>  
#include <limits>    


#define MAX_STRING_SIZE 51 


void updateProperty(Property properties[], int& propertyCount);


int getPropertyByRefNumber(int refNumber, const Property properties[], int propertyCount);


bool updateRefNumber(Property properties[], int propertyCount, int index);


bool updateStringField(char* fieldPtr, int maxSize, const char* fieldName);


template <typename T>
bool updateNumericField(T* fieldPtr, const char* fieldName) {
    std::cout << "Въведете нова стойност за " << fieldName << " (текуща: " << *fieldPtr << ", въведете -1 за запазване): ";
    T newValue;
    std::cin >> newValue;

    if (std::cin.fail()) {
        std::cout << "Невалиден вход. Запазена е текущата стойност.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    } else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (newValue != -1) { 
            *fieldPtr = newValue;
            return true;
        }
    }
    return false;
}


bool updateStatus(Property& propertyToUpdate);

#endif 