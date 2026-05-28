/**
 * @file file.h
 * @brief Declares functions for handling persistent data storage and retrieval.
 *
 * Provides functionality to save and load property data from binary files,
 * save data to user-friendly text files, manage synchronization with recovery files,
 * and handle confirmation for overwriting existing files.
 */

#ifndef FILE_H
#define FILE_H

#include "structs.h" // Necessary for Property type

/**
 * @brief Saves the current array of properties to a binary file.
 * @param properties Constant array of Property structures to save.
 * @param propertyCount The number of properties in the array.
 *
 * Serializes property data into a binary format for efficient storage
 * and retrieval, typically used for the main data file.
 */
void saveToBinaryFile(const Property properties[], int propertyCount);

/**
 * @brief Loads properties from a binary file into application memory.
 * @param properties Array of Property structures where loaded data will be stored.
 * @param propertyCount Reference to an integer that will hold the number of loaded properties.
 *
 * Deserializes property data from a binary file, populating the `properties` array
 * and updating `propertyCount`. Typically called at application startup.
 */
void loadFromBinaryFile(Property properties[], int& propertyCount);

/**
 * @brief Saves the current array of properties to a recovery binary file.
 * @param properties Constant array of Property structures to save.
 * @param propertyCount The number of properties in the array.
 *
 * Creates a backup of property data in binary format,
 * which can be used to restore data in case of unexpected application termination
 * or data corruption.
 */
void saveToRecoveryBinaryFile(const Property properties[], int propertyCount);

/**
 * @brief Saves the current array of properties to a readable text file.
 * @param properties Constant array of Property structures to save.
 * @param propertyCount The number of properties in the array.
 *
 * Exports property data to a formatted text file, making it
 * easy for users to view or share data outside the application.
 */
void saveToUserFriendlyTextFile(const Property properties[], int propertyCount);

/**
 * @brief Saves the current array of properties to a simple text file for synchronization purposes.
 * @param properties Constant array of Property structures to save.
 * @param propertyCount The number of properties in the array.
 *
 * This file format is typically simpler than the user-friendly one and may be optimized
 * for programmatic parsing during data synchronization processes.
 */
void saveToSyncTextFile(const Property properties[], int propertyCount);

/**
 * @brief Loads properties from a synchronization text file into application memory.
 * @param properties Array of Property structures where loaded data will be stored.
 * @param propertyCount Reference to an integer that will hold the number of loaded properties.
 *
 * Imports property data from a synchronization text file, parsing its content
 * and updating the property list in memory.
 */
void loadFromSyncTextFile(Property properties[], int& propertyCount);

/**
 * @brief Prompts the user for confirmation before overwriting an existing file.
 * @param filename The name of the file about to be overwritten.
 * @return true if the user confirms overwriting, false otherwise.
 *
 * Prevents accidental data loss when save operations might replace existing files.
 */
bool confirmOverwrite(const char* filename);

/**
 * @brief Synchronizes property data to recovery files (both binary and text).
 * @param properties Constant array of Property structures to synchronize.
 * @param propertyCount The number of properties in the array.
 *
 * Ensures that backup and synchronization files are up-to-date
 * with the current state of property data, providing multiple layers of data safety.
 */
void syncDataToRecoveryFiles(const Property properties[], int propertyCount);

#endif