

#include <iostream>    
#include <cstring>     
#include <iomanip>     

#include "reports.h"   
#include "structs.h"   
#include "display.h"   
#include "colors.h"    
#include "add.h"       
#include "utils.h"     
#include "localization.h" 

using namespace std;


void mostExpensiveInArea(const Property properties[], int propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }

    char searchArea[50];
    
    getValidStringInput((CYAN + getTranslatedString("PROMPT_REPORT_AREA") + RESET).c_str(), searchArea, sizeof(searchArea));

    double maxPrice = -1.0; 
    int mostExpensiveIndex = -1; 

    
    for (int i = 0; i < propertyCount; i++) {
        
        if (stringsEqualIgnoreCase(properties[i].area, searchArea)) {
            
            if (properties[i].price > maxPrice) {
                maxPrice = properties[i].price;
                mostExpensiveIndex = i; 
            }
        }
    }

    
    if (mostExpensiveIndex == -1) {
        cout << endl;
        cout << RED << getTranslatedString("NO_PROPERTY_FOUND_IN_AREA") << RESET << endl;
        return;
    }

    cout << YELLOW << "\n--- " << getTranslatedString("MOST_EXPENSIVE_PROPERTY_IN_AREA") << " " << searchArea << " ---" << RESET << endl;
    
    displayPropertyDetails(properties[mostExpensiveIndex]);
}


void averagePriceInArea(const Property properties[], int propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }

    char searchArea[50];
    
    getValidStringInput((CYAN + getTranslatedString("PROMPT_REPORT_AREA") + RESET).c_str(), searchArea, sizeof(searchArea));

    double totalPrice = 0.0;     
    int propertiesInAreaCount = 0; 

    
    for (int i = 0; i < propertyCount; i++) {
        if (stringsEqualIgnoreCase(properties[i].area, searchArea)) {
            totalPrice += properties[i].price;
            propertiesInAreaCount++;
        }
    }

    
    if (propertiesInAreaCount == 0) {
        cout << RED << getTranslatedString("NO_PROPERTIES_FOUND_IN_AREA") << RESET << endl;
        return;
    }

    cout << YELLOW << "\n--- " << getTranslatedString("FOUND_PROPERTIES_COUNT_PART1") << " " << propertiesInAreaCount << " " << getTranslatedString("FOUND_PROPERTIES_COUNT_PART2") << " " << totalPrice << " ---" << RESET << endl;
    cout << getTranslatedString("AVERAGE_PRICE_IN_AREA_PART1") << " '" << searchArea << " ' " << getTranslatedString("AVERAGE_PRICE_IN_AREA_PART2") << " " << fixed << setprecision(2) << totalPrice / propertiesInAreaCount << "." << endl;
}


void soldPercentagePerBroker(const Property properties[], int propertyCount) {
    if (propertyCount == 0) {
        cout << YELLOW << getTranslatedString("NO_PROPERTIES_IN_SYSTEM") << RESET << endl;
        return;
    }

    
    
    
    char brokerNames[MAX_PROPERTIES][50];
    int totalProperties[MAX_PROPERTIES] = {0}; 
    int soldProperties[MAX_PROPERTIES] = {0};
    int uniqueBrokersCount = 0;

    
    for (int i = 0; i < propertyCount; i++) {
        const Property& prop = properties[i];
        
        
        int brokerIndex = -1;
        for (int j = 0; j < uniqueBrokersCount; j++) {
            if (strcmp(brokerNames[j], prop.broker) == 0) {
                brokerIndex = j;
                break;
            }
        }

        
        if (brokerIndex == -1) {
            brokerIndex = uniqueBrokersCount;
            strncpy(brokerNames[brokerIndex], prop.broker, 49);
            brokerNames[brokerIndex][49] = '\0';
            uniqueBrokersCount++;
        }

        
        totalProperties[brokerIndex]++;
        if (prop.status == SOLD) {
            soldProperties[brokerIndex]++;
        }
    }

    cout << YELLOW << "\n--- " << getTranslatedString("SOLD_PERCENTAGE_PER_BROKER_HEADER") << " ---" << RESET << endl;

    
    for (int i = 0; i < uniqueBrokersCount; i++) {
        double soldBrokerPercentage = 0.0;
        if (totalProperties[i] > 0) {
            soldBrokerPercentage = (static_cast<double>(soldProperties[i]) / totalProperties[i]) * 100.0;
        }

        cout << getTranslatedString("BROKER_LABEL") << ": " << brokerNames[i] << endl;
        cout << left; 
        cout << "  " << setw(20) << getTranslatedString("TOTAL_PROPERTIES_LABEL") << totalProperties[i] << endl;
        cout << "  " << setw(20) << getTranslatedString("SOLD_PROPERTIES_LABEL") << soldProperties[i] << endl;
        cout << "  " << setw(20) << getTranslatedString("SOLD_PERCENTAGE_LABEL") << fixed << setprecision(2) << soldBrokerPercentage << "%" << endl;
        cout << endl;
    }
}
