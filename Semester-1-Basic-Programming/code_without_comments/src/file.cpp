

#include <iostream>    
#include <cstring>     
#include <fstream>     
#include <iomanip>     
#include <sstream>     
#include <limits>      
#include <cstdlib>     
#include <string>      
#include <algorithm>   

#include "file.h"      
#include "structs.h"   
#include "colors.h"    
#include "utils.h"     
#include "localization.h" 


using namespace std;




#ifdef PROJECT_ROOT_DIR
const string BASE_DIR = PROJECT_ROOT_DIR;
#else


const string BASE_DIR = ".";
#endif


const string USER_BINARY_FILENAME = BASE_DIR + "/data/properties_backup.dat"; 
const string USER_TEXT_FILENAME = BASE_DIR + "/data/properties_report.txt";   
const string SYNC_TEXT_FILENAME = BASE_DIR + "/data/recovery/sync.txt";       
const string SYNC_BINARY_FILENAME = BASE_DIR + "/data/recovery/sync.dat";     


void saveToBinaryFile(const Property properties[], int propertyCount) {
    
    ensureDirectoryExists((BASE_DIR + "/data").c_str());

    
    if (!confirmOverwrite(USER_BINARY_FILENAME.c_str())) {
        cout << YELLOW << getTranslatedString("SAVE_CANCELLED") << RESET << endl;
        return; 
    }

    
    ofstream outFile(USER_BINARY_FILENAME, ios::binary);
    if (!outFile) {
        cout << RED << getTranslatedString("ERROR_OPEN_FILE_WRITE") << RESET << endl;
        return; 
    }

    
    outFile.write(reinterpret_cast<const char*>(&propertyCount), sizeof(int));
    
    
    if (propertyCount > 0) {
        outFile.write(reinterpret_cast<const char*>(properties), sizeof(Property) * propertyCount);
    }
    
    outFile.close(); 

    cout << GREEN << getTranslatedString("DATA_SAVED_SUCCESS") << " '" << USER_BINARY_FILENAME << "'." << RESET << endl;
}


void loadFromBinaryFile(Property properties[], int& propertyCount) {
    
    ifstream inFile(USER_BINARY_FILENAME, ios::binary);
    if (!inFile) {
        cout << RED << getTranslatedString("ERROR_FILE_NOT_FOUND") << RESET << endl;
        propertyCount = 0; 
        return;
    }

    
    inFile.read(reinterpret_cast<char*>(&propertyCount), sizeof(int));
    
    
    if (inFile.gcount() != sizeof(int) || propertyCount < 0) {
        cout << RED << getTranslatedString("ERROR_FILE_CORRUPTED") << RESET << endl;
        inFile.close();
        propertyCount = 0;
        return;
    }

    
    if (propertyCount > 0 && propertyCount <= MAX_PROPERTIES) {
        inFile.read(reinterpret_cast<char*>(properties), sizeof(Property) * propertyCount);
        
        
        if (inFile.gcount() != (streamsize)(sizeof(Property) * propertyCount)) {
            cout << RED << getTranslatedString("ERROR_FILE_CORRUPTED_INCOMPLETE") << RESET << endl;
            propertyCount = 0;
            return;
        }

        cout << GREEN << getTranslatedString("DATA_LOADED_SUCCESS_COUNT") << " " << propertyCount << " " << getTranslatedString("DATA_LOADED_SUCCESS_FROM_FILE") << " '" << USER_BINARY_FILENAME << "'." << RESET << endl;
    } else if (propertyCount > MAX_PROPERTIES) {
        
        cout << RED << getTranslatedString("ERROR_CAPACITY_EXCEEDED_FILE_COUNT") << " (" << propertyCount << ") " << getTranslatedString("ERROR_CAPACITY_EXCEEDED_MAX_CAPACITY") << RESET << endl;
        propertyCount = 0; 
    } else { 
        cout << YELLOW << getTranslatedString("FILE_EMPTY_LOADED_ZERO") << RESET << endl;
        propertyCount = 0;
    }

    inFile.close(); 
}


void saveToUserFriendlyTextFile(const Property properties[], int propertyCount) {
    
    ensureDirectoryExists((BASE_DIR + "/data").c_str());
    
    if (!confirmOverwrite(USER_TEXT_FILENAME.c_str())) return;

    
    ofstream outFile(USER_TEXT_FILENAME);
    if (!outFile) {
        cout << RED << getTranslatedString("ERROR_OPEN_TEXT_FILE_WRITE") << RESET << endl;
        return;
    }

    
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

    
    outFile << fixed << setprecision(2);

    
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

    outFile.close(); 
    cout << GREEN << getTranslatedString("DATA_EXPORTED_SUCCESS") << " '" << USER_TEXT_FILENAME << "'." << RESET << endl;
}


void saveToSyncTextFile(const Property properties[], int propertyCount) {
    
    ofstream outFile(SYNC_TEXT_FILENAME);
    if (!outFile) return; 

    outFile << fixed << setprecision(2);

    
    for (int i = 0; i < propertyCount; i++) {
        const Property& prop = properties[i];
        outFile << prop.refNumber << "|" << prop.broker << "|" << prop.type << "|" << prop.area << "|" 
                << prop.exposition << "|" << prop.price << "|" << prop.totalArea << "|" 
                << prop.rooms << "|" << prop.floor << "|" << (int)prop.status << endl;
    }
    outFile.close(); 
}


void loadFromSyncTextFile(Property properties[], int& propertyCount) {
    
    ifstream inFile(SYNC_TEXT_FILENAME);
    if (!inFile) {
        propertyCount = 0; 
        return;
    }

    Property tempProps[MAX_PROPERTIES]; 
    int tempCount = 0;                  

    string line;
    
    while (tempCount < MAX_PROPERTIES && getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string segment;
        string segments[10]; 
        int segmentCount = 0;

        
        while (getline(ss, segment, '|') && segmentCount < 10) {
            segments[segmentCount++] = segment;
        }

        if (segmentCount != 10) continue; 

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
            continue; 
        }
    }

    inFile.close(); 

    
    if (tempCount == 0) {
        propertyCount = 0;
        return;
    }

    
    cout << getTranslatedString("RECOVERY_PROMPT_PART1") << " " << tempCount << " " << getTranslatedString("RECOVERY_PROMPT_PART2") << " [y/n] ";

    string answer;
    getline(cin, answer);

    
    if (answer.empty() || tolower(answer[0]) != 'y') {
        propertyCount = 0;
        return;
    }

    
    for (int i = 0; i < tempCount; i++) {
        properties[i] = tempProps[i];
    }
    propertyCount = tempCount; 

    cout << GREEN << getTranslatedString("DATA_LOADED_SUCCESS_COUNT") << " " << tempCount << " " << getTranslatedString("DATA_LOADED_SUCCESS_FROM_SYNC_FILE") << RESET << endl;
}



void syncDataToRecoveryFiles(const Property properties[], int propertyCount) {
    
    ensureDirectoryExists((BASE_DIR + "/data/recovery").c_str());
    
    saveToSyncTextFile(properties, propertyCount);
    
    saveToRecoveryBinaryFile(properties, propertyCount);
}


void saveToRecoveryBinaryFile(const Property properties[], int propertyCount) {
    
    ofstream outFile(SYNC_BINARY_FILENAME, ios::binary);
    if (!outFile) return; 

    
    outFile.write(reinterpret_cast<const char*>(&propertyCount), sizeof(int));
    
    if (propertyCount > 0) {
        outFile.write(reinterpret_cast<const char*>(properties), sizeof(Property) * propertyCount);
    }
    outFile.close(); 
}


bool confirmOverwrite(const char* filename) {
    
    ifstream fileCheck(filename);
    if (!fileCheck.good()) {
        return true; 
    }
    fileCheck.close(); 

    
    cout << YELLOW << getTranslatedString("FILE_EXISTS_OVERWRITE_PROMPT_PART1") << " '" << filename << "' " << getTranslatedString("FILE_EXISTS_OVERWRITE_PROMPT_PART2") << RESET;
    char choice;
    cin >> choice; 

    
    if (!cin) cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    
    return (choice == 'y' || choice == 'Y');
}