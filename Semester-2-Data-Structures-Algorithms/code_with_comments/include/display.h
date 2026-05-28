/**
 * @file display.h
 * @brief Declares functions for displaying property information.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "structs.h"

void displayAllProperties(Node* head);
void displaySoldProperties(Node* head);
void displayLargestProperties(Node* head);
void displayPropertyDetails(const Property& prop);
bool isPropertiesEmpty(Node* head);

#endif // DISPLAY_H