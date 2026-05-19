/**
 * @file structs.h
 * @brief Defines the core data structures and enumerations used in the system.
 *
 * Includes the definition for the Property structure, which represents a single real estate listing,
 * and the Status enumeration, which indicates property availability.
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

// Defines the maximum number of properties I can handle in certain contexts.
#define MAX_PROPERTIES 100

/**
 * @brief Enumerates the possible statuses of a real estate property.
 *
 * - SOLD: The property is sold and no longer available.
 * - RESERVED: The property is temporarily reserved for a potential buyer.
 * - AVAILABLE: The property is currently on the market and available for purchase.
 */
enum Status { SOLD, RESERVED, AVAILABLE };

/**
 * @brief Converts a Status enum value to its corresponding string representation.
 * @param status The Status value to convert.
 * @return A string representing the status.
 */
std::string getStatusString(enum Status status);

/**
 * @brief Represents a single real estate property with various attributes.
 */
struct Property {
    int refNumber;      ///< Unique reference number for the property.
    char broker[50];    ///< Name of the broker handling the property.
    char type[50];      ///< Type of property (e.g., apartment, house, land).
    char area[50];      ///< Location or specific area of the property.
    char exposition[20];///< Orientation or exposition of the property (e.g., south, northeast).
    double price;       ///< Selling price of the property.
    double totalArea;   ///< Total area of the property in square meters.
    int rooms;          ///< Number of rooms in the property.
    int floor;          ///< Floor number where the property is located (0 for ground floor).
    enum Status status; ///< Current status of the property (SOLD, RESERVED, AVAILABLE).
};

#endif //STRUCTS_H