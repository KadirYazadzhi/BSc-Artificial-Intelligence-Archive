

#ifndef ADD_H
#define ADD_H

#include "structs.h" 
#include <limits>    
#include <iostream>  


void addSingleProperty(Property properties[], int& propertyCount);


void addMultipleProperties(Property properties[], int& propertyCount);


template <typename T> T getValidNumericInput(const char* prompt, const char* errorMsg = "Невалиден вход. Опитайте отново: ") {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << errorMsg;
            std::cin.clear(); 
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}


bool isCapacityReached(int propertyCount);


void sanitizeString(char* str);


void getValidStringInput(const char* prompt, char* buffer, int bufferSize);

#endif 