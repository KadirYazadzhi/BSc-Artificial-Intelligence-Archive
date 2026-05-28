#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <cstring> // for strncpy
#include "test_data.h"
#include "file.h"      // for syncDataToRecoveryFiles
#include "colors.h"    // for colors
#include "localization.h" // for getTranslatedString

// Data Pools for random generation (English)

// List of 10 fictional broker names
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

// List of property types
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

// List of fictional or generic areas/neighborhoods
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

// List of cardinal and ordinal directions for exposition
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

/**
 * @brief Generates random test properties.
 * 
 * Populates the system with random data mixing the static arrays above.
 * It aims to fill the system up to 85 properties to allow for meaningful testing
 * of sorting and search algorithms.
 */
void generateTestProperties(Property properties[], int& propertyCount) {
    std::srand(std::time(0)); // Initialize random number generator

    int targetCount = 85; // Goal: have 85 properties for testing
    int addedCount = 0;

    // Loop until goal reached or array full
    while (propertyCount < targetCount && propertyCount < MAX_PROPERTIES) {
        Property prop;

        // Generate unique reference number (simple counter + 1000)
        prop.refNumber = 1000 + propertyCount + 1;

        // Pick random indices from data pools
        int brokerIdx = std::rand() % BROKERS_COUNT;
        int typeIdx = std::rand() % TYPES_COUNT;
        int areaIdx = std::rand() % AREAS_COUNT;
        int expoIdx = std::rand() % EXPOSITIONS_COUNT;

        // Copy strings safely
        strncpy(prop.broker, BROKERS[brokerIdx], sizeof(prop.broker) - 1);
        prop.broker[sizeof(prop.broker) - 1] = '\0';

        strncpy(prop.type, TYPES[typeIdx], sizeof(prop.type) - 1);
        prop.type[sizeof(prop.type) - 1] = '\0';

        strncpy(prop.area, AREAS[areaIdx], sizeof(prop.area) - 1);
        prop.area[sizeof(prop.area) - 1] = '\0';

        strncpy(prop.exposition, EXPOSITIONS[expoIdx], sizeof(prop.exposition) - 1);
        prop.exposition[sizeof(prop.exposition) - 1] = '\0';

        // Generate numeric data
        // Price between 50,000 and 500,000
        prop.price = 50000.0 + (std::rand() % 450001);
        
        // Area between 40 and 200 sq.m.
        prop.totalArea = 40.0 + (std::rand() % 161);
        
        // Rooms: rough logic based on area (e.g., 1 room per 40 sq.m) + small randomness
        prop.rooms = (int)(prop.totalArea / 40) + (std::rand() % 2);
        if (prop.rooms < 1) prop.rooms = 1;

        // Floor between 1 and 15
        prop.floor = 1 + (std::rand() % 15);

        // Default status
        prop.status = AVAILABLE;

        // Add to array
        properties[propertyCount] = prop;
        propertyCount++;
        addedCount++;
    }

    if (addedCount > 0) {
        // Save immediately to recovery files so data isn't lost
        syncDataToRecoveryFiles(properties, propertyCount);
        std::cout << GREEN << getTranslatedString("TEST_DATA_GENERATED_SUCCESS_PART1") << addedCount << getTranslatedString("TEST_DATA_GENERATED_SUCCESS_PART2") << RESET << std::endl;
    } else {
        std::cout << YELLOW << getTranslatedString("TEST_DATA_CAPACITY_REACHED") << RESET << std::endl;
    }
}