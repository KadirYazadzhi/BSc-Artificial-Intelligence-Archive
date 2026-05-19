/**
 * @file file.cpp
 * @brief Implementation of all file operations for the real estate management system.
 *
 * This file handles saving and loading property data from and to various file formats,
 * including binary files for efficient storage, user-friendly text files for reports,
 * and synchronization files for data recovery. Also includes utilities for
 * directory management and file overwrite confirmation.
 */

#include <iostream>    // Necessary for standard I/O operations (cout, cin, cerr)
#include <cstring>     // Necessary for C-string manipulation (strcpy, etc.)
#include <fstream>     // Necessary for file stream operations (ifstream, ofstream)
#include <iomanip>     // Necessary for output formatting (setw, setprecision)
#include <sstream>     // Necessary for string parsing (stringstream)
#include <limits>      // Necessary for numeric_limits (used with cin.ignore)
#include <cstdlib>     // Necessary for system() (used in ensureDirectoryExists)
#include <string>      // Necessary for std::string manipulations
#include <algorithm>   // Necessary for std::tolower with characters

#include "file.h"      // Header for file operation declarations
#include "structs.h"   // Defines Property structure and Status enum
#include "colors.h"    // Defines ANSI escape codes for console coloring
#include "utils.h"     // Helper functions like ensureDirectoryExists, getConfirmation
#include "localization.h" // Localization functions like getTranslatedString


using namespace std;

// Defines the base directory using the preprocessor definition from CMake.
// This ensures that file paths are correctly resolved relative to the project root directory
// regardless of the current working directory at runtime.
#ifdef PROJECT_ROOT_DIR
const string BASE_DIR = PROJECT_ROOT_DIR;
#else
// Fallback when PROJECT_ROOT_DIR is not defined (e.g., if not compiled with CMake
// or for local testing outside the build system). Assumes '.' as the base directory.
const string BASE_DIR = ".";
#endif

// Definitions of absolute file paths used for various data storage purposes.
const string USER_BINARY_FILENAME = BASE_DIR + "/data/properties_backup.dat"; // Main binary backup file
const string USER_TEXT_FILENAME = BASE_DIR + "/data/properties_report.txt";   // Readable text report
const string SYNC_TEXT_FILENAME = BASE_DIR + "/data/recovery/sync.txt";       // Text file for recovery/sync
const string SYNC_BINARY_FILENAME = BASE_DIR + "/data/recovery/sync.dat";     // Binary file for recovery/sync

/**
 * @brief Saves the current array of properties to a user-specified binary file.
 *
 * First ensures that the target directory exists. Then prompts the
 * user for confirmation if the file already exists, to prevent accidental overwrites.
 * Property data is written in raw binary format, starting with `propertyCount`
 * and followed by the array of `Property` structures.
 *
 * @param properties Constant array of `Property` structures to save.
 * @param propertyCount The number of valid properties in the array.
 */
void saveToBinaryFile(const Property properties[], int propertyCount) {
    // Ensures the data directory exists before attempting to write files.
    ensureDirectoryExists((BASE_DIR + "/data").c_str());

    // Confirms with the user if they want to overwrite an existing file.
    if (!confirmOverwrite(USER_BINARY_FILENAME.c_str())) {
        cout << YELLOW << getTranslatedString("SAVE_CANCELLED") << RESET << endl;
        return; // Abort save operation if not confirmed.
    }

    // Opens the file in binary write mode.
    ofstream outFile(USER_BINARY_FILENAME, ios::binary);
    if (!outFile) {
        cout << RED << getTranslatedString("ERROR_OPEN_FILE_WRITE") << RESET << endl;
        return; // Handle file open error.
    }

    // Writes the total number of properties first.
    outFile.write(reinterpret_cast<const char*>(&propertyCount), sizeof(int));
    
    // If properties exist, writes the entire array.
    if (propertyCount > 0) {
        outFile.write(reinterpret_cast<const char*>(properties), sizeof(Property) * propertyCount);
    }
    
    outFile.close(); // Closes the file.

    cout << GREEN << getTranslatedString("DATA_SAVED_SUCCESS") << " '" << USER_BINARY_FILENAME << "'." << RESET << endl;
}

/**
 * @brief Loads property data from a user-specified binary file into application memory.
 *
 * Attempts to open a binary file and read property data from it.
 * Reads the number of properties first, then the array of `Property` structures.
 * Robust error checking is included to handle cases where the file is not found,
 * is corrupted, or if the property count exceeds application capacity.
 *
 * @param properties Array of `Property` structures where loaded data will be stored.
 * @param propertyCount Reference to an integer that will be updated with the count of loaded properties.
 */
void loadFromBinaryFile(Property properties[], int& propertyCount) {
    // Opens the file in binary read mode.
    ifstream inFile(USER_BINARY_FILENAME, ios::binary);
    if (!inFile) {
        cout << RED << getTranslatedString("ERROR_FILE_NOT_FOUND") << RESET << endl;
        propertyCount = 0; // Reset property count if file not found.
        return;
    }

    // Reads the number of properties from the file.
    inFile.read(reinterpret_cast<char*>(&propertyCount), sizeof(int));
    
    // Validates the number of items read and the integrity of propertyCount.
    if (inFile.gcount() != sizeof(int) || propertyCount < 0) {
        cout << RED << getTranslatedString("ERROR_FILE_CORRUPTED") << RESET << endl;
        inFile.close();
        propertyCount = 0;
        return;
    }

    // If properties exist and are within capacity, reads them.
    if (propertyCount > 0 && propertyCount <= MAX_PROPERTIES) {
        inFile.read(reinterpret_cast<char*>(properties), sizeof(Property) * propertyCount);
        
        // Checks if all expected properties were read.
        if (inFile.gcount() != (streamsize)(sizeof(Property) * propertyCount)) {
            cout << RED << getTranslatedString("ERROR_FILE_CORRUPTED_INCOMPLETE") << RESET << endl;
            propertyCount = 0;
            return;
        }

        cout << GREEN << getTranslatedString("DATA_LOADED_SUCCESS_COUNT") << " " << propertyCount << " " << getTranslatedString("DATA_LOADED_SUCCESS_FROM_FILE") << " '" << USER_BINARY_FILENAME << "'." << RESET << endl;
    } else if (propertyCount > MAX_PROPERTIES) {
        // Handles case where file contains more properties than application can handle.
        cout << RED << getTranslatedString("ERROR_CAPACITY_EXCEEDED_FILE_COUNT") << " (" << propertyCount << ") " << getTranslatedString("ERROR_CAPACITY_EXCEEDED_MAX_CAPACITY") << RESET << endl;
        propertyCount = 0; // Discard loaded data to prevent overflow.
    } else { // propertyCount is 0, meaning file was empty.
        cout << YELLOW << getTranslatedString("FILE_EMPTY_LOADED_ZERO") << RESET << endl;
        propertyCount = 0;
    }

    inFile.close(); // Closes the file.
}

/**
 * @brief Saves the current array of properties to a readable text file as a report.
 *
 * Formats property data into a tabular text report. Includes
 * headers and separators for readability and uses localized strings for column names.
 * Like `saveToBinaryFile`, checks for directory existence and confirms overwrites.
 *
 * @param properties Constant array of `Property` structures to report.
 * @param propertyCount The number of valid properties in the array.
 */
void saveToUserFriendlyTextFile(const Property properties[], int propertyCount) {
    // Ensures the data directory exists.
    ensureDirectoryExists((BASE_DIR + "/data").c_str());
    // Confirms overwrite if file exists.
    if (!confirmOverwrite(USER_TEXT_FILENAME.c_str())) return;

    // Opens the file in write mode.
    ofstream outFile(USER_TEXT_FILENAME);
    if (!outFile) {
        cout << RED << getTranslatedString("ERROR_OPEN_TEXT_FILE_WRITE") << RESET << endl;
        return;
    }

    // Prints table headers and separators.
    outFile << "----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    outFile << "| " << left << setw(4) << getTranslatedString("REF_SHORT") 
            << " | " << setw(20) << getTranslatedString("BROKER_SHORT")
            << " | " << setw(15) << getTranslatedString("TYPE_SHORT")
            << " | " << setw(20) << getTranslatedString("AREA_SHORT")
            << " | " << setw(12) << getTranslatedString("EXPOSITION_SHORT")
            << " | " << setw(16) << getTranslatedString("PRICE_SHORT")
            << " | " << setw(10) << getTranslatedString("TOTAL_AREA_SHORT")
            << " | " << setw(5) << getTranslatedString("ROOMS_SHORT")
            << " | " << setw(5) << getTranslatedString("FLOOR_SHORT")
            << " | " << setw(10) << getTranslatedString("STATUS_SHORT") << " |" << endl;
    outFile << "----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    // Sets formatting for floating-point numbers.
    outFile << fixed << setprecision(2);

    // Iterates through properties and prints their details.
    for (int i = 0; i < propertyCount; i++) {
        const Property& prop = properties[i];
        outFile << "| " << left << setw(4) << prop.refNumber
                << " | " << setw(20) << prop.broker
                << " | " << setw(15) << prop.type
                << " | " << setw(20) << prop.area
                << " | " << setw(12) << prop.exposition
                << " | " << setw(16) << prop.price
                << " | " << setw(10) << prop.totalArea
                << " | " << setw(5) << prop.rooms
                << " | " << setw(5) << prop.floor
                << " | " << setw(10) << getStatusString(prop.status) << " |" << endl;
    }

    outFile.close(); // Closes the file.
    cout << GREEN << getTranslatedString("DATA_EXPORTED_SUCCESS") << " '" << USER_TEXT_FILENAME << "'." << RESET << endl;
}

/**
 * @brief Saves the current array of properties to a simple text file for synchronization/recovery.
 *
 * Writes property data to a text file in a pipe-separated format.
 * This format is optimized for programmatic parsing during data load/recovery,
 * rather than human readability. File open error handling is minimal as
 * this is primarily an internal recovery mechanism.
 *
 * @param properties Constant array of `Property` structures to synchronize.
 * @param propertyCount The number of valid properties in the array.
 */
void saveToSyncTextFile(const Property properties[], int propertyCount) {
    // Opens the file in write mode.
    ofstream outFile(SYNC_TEXT_FILENAME);
    if (!outFile) return; // Returns silently on error.

    outFile << fixed << setprecision(2);

    // Writes each property's details in pipe-separated format.
    for (int i = 0; i < propertyCount; i++) {
        const Property& prop = properties[i];
        outFile << prop.refNumber << "|" << prop.broker << "|" << prop.type << "|" << prop.area << "|" 
                << prop.exposition << "|" << prop.price << "|" << prop.totalArea << "|" 
                << prop.rooms << "|" << prop.floor << "|" << (int)prop.status << endl;
    }
    outFile.close(); // Closes the file.
}

/**
 * @brief Loads property data from a synchronization text file into application memory.
 *
 * Reads property data from a pipe-separated text file. Parses
 * each line, constructs `Property` structures, and stores them in a temporary array.
 * After loading, prompts the user for confirmation to load these properties
 * into the main application data, providing a recovery mechanism.
 *
 * @param properties Array of `Property` structures where loaded data will be stored.
 * @param propertyCount Reference to an integer that will be updated with the count of loaded properties.
 */
void loadFromSyncTextFile(Property properties[], int& propertyCount) {
    // Opens the file in read mode.
    ifstream inFile(SYNC_TEXT_FILENAME);
    if (!inFile) {
        propertyCount = 0; // If file doesn't exist, no properties to load.
        return;
    }

    Property tempProps[MAX_PROPERTIES]; // Temporary array to store loaded properties.
    int tempCount = 0;                  // Count of properties loaded into tempProps.

    string line;
    // Reads properties from file line by line.
    while (tempCount < MAX_PROPERTIES && getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string segment;
        string segments[10]; // Static array instead of vector
        int segmentCount = 0;

        // Splits the line by '|' delimiter.
        while (getline(ss, segment, '|') && segmentCount < 10) {
            segments[segmentCount++] = segment;
        }

        if (segmentCount != 10) continue; // Skip invalid lines.

        Property& prop = tempProps[tempCount];
        try {
            prop.refNumber = stoi(segments[0]);
            
            strncpy(prop.broker, segments[1].c_str(), sizeof(prop.broker) - 1);
            prop.broker[sizeof(prop.broker) - 1] = '\0';
            
            strncpy(prop.type, segments[2].c_str(), sizeof(prop.type) - 1);
            prop.type[sizeof(prop.type) - 1] = '\0';
            
            strncpy(prop.area, segments[3].c_str(), sizeof(prop.area) - 1);
            prop.area[sizeof(prop.area) - 1] = '\0';
            
            strncpy(prop.exposition, segments[4].c_str(), sizeof(prop.exposition) - 1);
            prop.exposition[sizeof(prop.exposition) - 1] = '\0';

            prop.price = stod(segments[5]);
            prop.totalArea = stod(segments[6]);
            prop.rooms = stoi(segments[7]);
            prop.floor = stoi(segments[8]);
            
            int statusInt = stoi(segments[9]);
            if (statusInt >= SOLD && statusInt <= AVAILABLE) {
                prop.status = (Status)statusInt;
            } else {
                prop.status = AVAILABLE;
            }

            tempCount++;
        } catch (...) {
            continue; // Skip line on conversion error (stoi/stod)
        }
    }

    inFile.close(); // Closes the file.

    // If no properties loaded, return early.
    if (tempCount == 0) {
        propertyCount = 0;
        return;
    }

    // Prompts user for confirmation before loading recovered data.
    cout << getTranslatedString("RECOVERY_PROMPT_PART1") << " " << tempCount << " " << getTranslatedString("RECOVERY_PROMPT_PART2") << " [y/n] ";

    string answer;
    getline(cin, answer);

    // If user does not confirm, discard recovered data.
    if (answer.empty() || tolower(answer[0]) != 'y') {
        propertyCount = 0;
        return;
    }

    // Copies properties from temporary array to main property array.
    for (int i = 0; i < tempCount; i++) {
        properties[i] = tempProps[i];
    }
    propertyCount = tempCount; // Update main property count.

    cout << GREEN << getTranslatedString("DATA_LOADED_SUCCESS_COUNT") << " " << tempCount << " " << getTranslatedString("DATA_LOADED_SUCCESS_FROM_SYNC_FILE") << RESET << endl;
}


/**
 * @brief Synchronizes current property data with recovery text and binary files.
 *
 * Ensures data resilience by writing the current state of properties
 * to designated recovery files. First ensures the recovery directory exists,
 * then calls `saveToSyncTextFile` and `saveToRecoveryBinaryFile`. By using this multi-format
 * recovery strategy, it provides resilience against various types of data corruption.
 *
 * @param properties Constant array of `Property` structures to synchronize.
 * @param propertyCount The number of valid properties in the array.
 */
void syncDataToRecoveryFiles(const Property properties[], int propertyCount) {
    // Ensures the recovery directory structure is present.
    ensureDirectoryExists((BASE_DIR + "/data/recovery").c_str());
    // Writes to sync text file.
    saveToSyncTextFile(properties, propertyCount);
    // Writes to recovery binary file.
    saveToRecoveryBinaryFile(properties, propertyCount);
}

/**
 * @brief Saves the current array of properties to a recovery binary file.
 *
 * This is a specialized version of binary saving designed for automatic
 * background recovery. Writes property count and data directly
 * to a predefined binary file without user interaction or overwrite prompts,
 * ensuring a recent backup is always available.
 *
 * @param properties Constant array of `Property` structures to save.
 * @param propertyCount The number of valid properties in the array.
 */
void saveToRecoveryBinaryFile(const Property properties[], int propertyCount) {
    // Opens the recovery file in binary write mode.
    ofstream outFile(SYNC_BINARY_FILENAME, ios::binary);
    if (!outFile) return; // Fail silently.

    // Writes property count.
    outFile.write(reinterpret_cast<const char*>(&propertyCount), sizeof(int));
    // Writes property data if any.
    if (propertyCount > 0) {
        outFile.write(reinterpret_cast<const char*>(properties), sizeof(Property) * propertyCount);
    }
    outFile.close(); // Closes the file.
}

/**
 * @brief Prompts the user for confirmation before overwriting an existing file.
 *
 * Checks if a given file already exists. If it does, displays
 * a localized warning message to the user and asks for explicit confirmation
 * before proceeding with an operation that would overwrite the file.
 * This is a critical safety measure to prevent unintended data loss.
 *
 * @param filename C-style string path to the file in question.
 * @return `true` if the file does not exist or if the user confirms overwrite; `false` otherwise.
 */
bool confirmOverwrite(const char* filename) {
    // Checks if file exists.
    ifstream fileCheck(filename);
    if (!fileCheck.good()) {
        return true; // If file doesn't exist, no overwrite needed.
    }
    fileCheck.close(); // Close file check stream.

    // If file exists, prompt for confirmation.
    cout << YELLOW << getTranslatedString("FILE_EXISTS_OVERWRITE_PROMPT_PART1") << " '" << filename << "' " << getTranslatedString("FILE_EXISTS_OVERWRITE_PROMPT_PART2") << RESET;
    char choice;
    cin >> choice; // Reads user choice.

    // Clear cin error state if any and ignore remaining input.
    if (!cin) cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Returns true if choice is 'y' or 'Y', indicating confirmation.
    return (choice == 'y' || choice == 'Y');
}