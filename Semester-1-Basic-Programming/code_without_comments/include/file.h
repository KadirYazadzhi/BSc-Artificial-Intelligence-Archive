

#ifndef FILE_H
#define FILE_H

#include "structs.h" 


void saveToBinaryFile(const Property properties[], int propertyCount);


void loadFromBinaryFile(Property properties[], int& propertyCount);


void saveToRecoveryBinaryFile(const Property properties[], int propertyCount);


void saveToUserFriendlyTextFile(const Property properties[], int propertyCount);


void saveToSyncTextFile(const Property properties[], int propertyCount);


void loadFromSyncTextFile(Property properties[], int& propertyCount);


bool confirmOverwrite(const char* filename);


void syncDataToRecoveryFiles(const Property properties[], int propertyCount);

#endif