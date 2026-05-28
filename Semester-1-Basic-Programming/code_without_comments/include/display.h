

#ifndef DISPLAY_H
#define DISPLAY_H

#include "structs.h" 


void displayAllProperties(const Property properties[], int propertyCount);


void displaySoldProperties(const Property properties[], int propertyCount);


void displayLargestProperties(const Property properties[], int propertyCount);


void displayPropertyDetails(const Property& prop);


bool isPropertiesEmpty(int propertyCount);


#endif 