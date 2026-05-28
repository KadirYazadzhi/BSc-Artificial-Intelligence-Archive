/**
 * @file structs.h
 * @brief Defines the core data structures and enumerations used in the system.
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

/**
 * @brief Enumerates the possible statuses of a real estate property.
 */
enum Status { SOLD, RESERVED, AVAILABLE };

/**
 * @brief Converts a Status enum value to its corresponding string representation.
 */
std::string getStatusString(enum Status status);

/**
 * @brief Represents a single real estate property with various attributes.
 */
struct Property {
    int refNumber;      ///< Unique reference number for the property.
    char broker[50];    ///< Name of the broker handling the property.
    char type[50];      ///< Type of property.
    char area[50];      ///< Location or specific area.
    char exposition[20];///< Orientation or exposition.
    double price;       ///< Selling price.
    double totalArea;   ///< Total area in square meters.
    int rooms;          ///< Number of rooms.
    int floor;          ///< Floor number.
    enum Status status; ///< Current status.
};

/**
 * @brief Node for the linked list of properties.
 */
struct Node {
    Property data;
    Node* next;
};

#endif //STRUCTS_H