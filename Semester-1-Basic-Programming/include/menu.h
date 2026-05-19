/**
 * @file menu.h
 * @brief Declares functions responsible for displaying and managing application menus.
 *
 * Defines the structure and functionality of various menus, allowing users to navigate
 * through different features of the real estate management system, such as adding,
 * displaying, deleting, searching, sorting, file operations, and generating reports.
 */

#ifndef MENU_H
#define MENU_H

#include "structs.h" // Necessary for Property type

/**
 * @brief Displays the main application menu and handles user choices.
 * @param properties Array of Property structures representing the main dataset.
 * @param propertyCount Reference to an integer containing the current number of properties.
 *
 * This function serves as the central navigation hub, directing users to different
 * parts of the application based on their input.
 */
void mainMenu(Property properties[], int& propertyCount);

/**
 * @brief Displays the property addition menu and handles user choices.
 * @param properties Array of Property structures where new properties will be added.
 * @param propertyCount Reference to an integer containing the current number of properties.
 *
 * Allows users to choose between adding a single property or multiple properties.
 */
void addPropertyMenu(Property properties[], int& propertyCount);

/**
 * @brief Displays the property viewing menu and handles user choices.
 * @param properties Constant array of Property structures to display.
 * @param propertyCount The current number of properties in the system.
 *
 * Provides options to display all properties, sold properties, or properties sorted by size.
 */
void displayMenu(const Property properties[], int propertyCount);

/**
 * @brief Displays the property deletion menu and handles user choices.
 * @param properties Array of Property structures from which properties will be deleted.
 * @param propertyCount Reference to an integer containing the current number of properties.
 *
 * Allows users to delete a single property by reference number or clear all properties.
 */
void deletePropertyMenu(Property properties[], int& propertyCount);

/**
 * @brief Displays the property search menu and handles user choices.
 * @param properties Constant array of Property structures to search.
 * @param propertyCount The current number of properties in the system.
 *
 * Offers options to search properties by broker name or by number of rooms.
 */
void searchMenu(Property properties[], int propertyCount);

/**
 * @brief Displays the property sorting menu and handles user choices.
 * @param properties Array of Property structures to sort.
 * @param propertyCount The current number of properties in the system.
 *
 * Provides various criteria for sorting properties, such as price, area, or reference number.
 */
void sortMenu(Property properties[], int propertyCount);

/**
 * @brief Displays the file operations menu (save/load) and handles user choices.
 * @param properties Array of Property structures for file operations.
 * @param propertyCount Reference to an integer containing the current number of properties.
 *
 * Allows users to save data in various file formats (binary, text) and load data.
 */
void fileMenu(Property properties[], int& propertyCount);

/**
 * @brief Displays the report generation menu and handles user choices.
 * @param properties Constant array of Property structures for report generation.
 * @param propertyCount The current number of properties in the system.
 *
 * Offers options to generate analytical reports, such as most expensive in an area,
 * average price, or percentage sold by broker.
 */
void reportsMenu(const Property properties[], int propertyCount);

#endif //MENU_H