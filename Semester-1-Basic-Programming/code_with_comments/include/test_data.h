#ifndef TEST_DATA_H
#define TEST_DATA_H

#include "structs.h"

/**
 * @brief Generates random test properties to populate the system.
 * 
 * This function uses internal static arrays of data to generate
 * randomized properties and add them to the system until a target
 * count is reached or the array is full.
 * 
 * @param properties The array of properties to fill.
 * @param propertyCount Reference to the current count of properties.
 */
void generateTestProperties(Property properties[], int& propertyCount);

#endif // TEST_DATA_H