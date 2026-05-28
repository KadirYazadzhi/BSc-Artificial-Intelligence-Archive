#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <cstring> 
#include "test_data.h"
#include "file.h"      
#include "colors.h"    
#include "localization.h" 




const char* BROKERS[] = {
    "John Smith",
    "Sarah Connor",
    "Michael Johnson",
    "Emily Davis",
    "David Wilson",
    "Jessica Taylor",
    "Robert Brown",
    "Jennifer White",
    "William Harris",
    "Elizabeth Martin"
};
const int BROKERS_COUNT = 10;


const char* TYPES[] = {
    "Apartment",
    "House",
    "Villa",
    "Studio",
    "Penthouse",
    "Office",
    "Warehouse",
    "Maisonette"
};
const int TYPES_COUNT = 8;


const char* AREAS[] = {
    "Downtown",
    "Suburbs",
    "Old Town",
    "Financial District",
    "Green Valley",
    "West Side",
    "East End",
    "North Hills",
    "South Beach",
    "Industrial Park"
};
const int AREAS_COUNT = 10;


const char* EXPOSITIONS[] = {
    "North",
    "South",
    "East",
    "West",
    "North-East",
    "North-West",
    "South-East",
    "South-West"
};
const int EXPOSITIONS_COUNT = 8;


void generateTestProperties(Property properties[], int& propertyCount) {
    std::srand(std::time(0)); 

    int targetCount = 85; 
    int addedCount = 0;

    
    while (propertyCount < targetCount && propertyCount < MAX_PROPERTIES) {
        Property prop;

        
        prop.refNumber = 1000 + propertyCount + 1;

        
        int brokerIdx = std::rand() % BROKERS_COUNT;
        int typeIdx = std::rand() % TYPES_COUNT;
        int areaIdx = std::rand() % AREAS_COUNT;
        int expoIdx = std::rand() % EXPOSITIONS_COUNT;

        
        strncpy(prop.broker, BROKERS[brokerIdx], sizeof(prop.broker) - 1);
        prop.broker[sizeof(prop.broker) - 1] = '\0';

        strncpy(prop.type, TYPES[typeIdx], sizeof(prop.type) - 1);
        prop.type[sizeof(prop.type) - 1] = '\0';

        strncpy(prop.area, AREAS[areaIdx], sizeof(prop.area) - 1);
        prop.area[sizeof(prop.area) - 1] = '\0';

        strncpy(prop.exposition, EXPOSITIONS[expoIdx], sizeof(prop.exposition) - 1);
        prop.exposition[sizeof(prop.exposition) - 1] = '\0';

        
        
        prop.price = 50000.0 + (std::rand() % 450001);
        
        
        prop.totalArea = 40.0 + (std::rand() % 161);
        
        
        prop.rooms = (int)(prop.totalArea / 40) + (std::rand() % 2);
        if (prop.rooms < 1) prop.rooms = 1;

        
        prop.floor = 1 + (std::rand() % 15);

        
        prop.status = AVAILABLE;

        
        properties[propertyCount] = prop;
        propertyCount++;
        addedCount++;
    }

    if (addedCount > 0) {
        
        syncDataToRecoveryFiles(properties, propertyCount);
        std::cout << GREEN << getTranslatedString("TEST_DATA_GENERATED_SUCCESS_PART1") << addedCount << getTranslatedString("TEST_DATA_GENERATED_SUCCESS_PART2") << RESET << std::endl;
    } else {
        std::cout << YELLOW << getTranslatedString("TEST_DATA_CAPACITY_REACHED") << RESET << std::endl;
    }
}