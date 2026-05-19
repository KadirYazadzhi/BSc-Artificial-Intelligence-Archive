/**
 * @file menu.h
 * @brief Declares functions for managing application menus.
 */

#ifndef MENU_H
#define MENU_H

#include "structs.h"

void mainMenu(Node*& head);
void addPropertyMenu(Node*& head);
void displayMenu(Node* head);
void deletePropertyMenu(Node*& head);
void searchMenu(Node* head);
void sortMenu(Node* head);
void reportsMenu(Node* head);

#endif //MENU_H