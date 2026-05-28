

#ifndef MENU_H
#define MENU_H

#include "structs.h" 


void mainMenu(Property properties[], int& propertyCount);


void addPropertyMenu(Property properties[], int& propertyCount);


void displayMenu(const Property properties[], int propertyCount);


void deletePropertyMenu(Property properties[], int& propertyCount);


void searchMenu(Property properties[], int propertyCount);


void sortMenu(Property properties[], int propertyCount);


void fileMenu(Property properties[], int& propertyCount);


void reportsMenu(const Property properties[], int propertyCount);

#endif 