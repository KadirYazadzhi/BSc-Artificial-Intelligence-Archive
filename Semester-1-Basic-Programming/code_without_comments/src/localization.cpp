

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits> 
#include <string>   
#include <cstring> 

#include "localization.h"
#include "utils.h" 
#include "colors.h" 



#ifdef PROJECT_ROOT_DIR
const std::string BASE_DIR = PROJECT_ROOT_DIR;
#else


const std::string BASE_DIR = ".";
#endif





TranslationEntry g_translations[MAX_TRANSLATIONS];
int g_translationCount = 0; 


std::string currentLanguage = "bg"; 


void loadTranslations(const std::string& langCode) {
    g_translationCount = 0; 

    
    std::string filename = BASE_DIR + "/lang/" + langCode + ".txt"; 
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << RED << "Error: Could not open translation file: / Грешка: Не може да се отвори файлът с преводи: " << filename << RESET << std::endl;
        
        
        if (langCode != "bg") {
            currentLanguage = "bg"; 
            loadTranslations("bg");
        }
        return; 
    }

    std::string line;
    
    while (std::getline(file, line) && g_translationCount < MAX_TRANSLATIONS) {
        size_t delimiterPos = line.find('='); 
        if (delimiterPos != std::string::npos) {
            std::string key_str = line.substr(0, delimiterPos); 
            std::string value_str = line.substr(delimiterPos + 1); 

            
            strncpy(g_translations[g_translationCount].key, key_str.c_str(), MAX_TRANSLATION_STRING_LENGTH - 1);
            g_translations[g_translationCount].key[MAX_TRANSLATION_STRING_LENGTH - 1] = '\0';

            
            strncpy(g_translations[g_translationCount].value, value_str.c_str(), MAX_TRANSLATION_STRING_LENGTH - 1);
            g_translations[g_translationCount].value[MAX_TRANSLATION_STRING_LENGTH - 1] = '\0';
            
            g_translationCount++; 
        }
    }
    file.close(); 
    currentLanguage = langCode; 
}


std::string getTranslatedString(const std::string& key) {
    for (int i = 0; i < g_translationCount; ++i) {
        if (strcmp(g_translations[i].key, key.c_str()) == 0) {
            return std::string(g_translations[i].value);
        }
    }
    
    std::cerr << YELLOW << "Warning: Translation key '" << key << "' not found for language '" << currentLanguage << "'. / Предупреждение: Ключ за превод '" << key << "' не е намерен за език '" << currentLanguage << "'." << RESET << std::endl;
    return key;
}


void selectLanguage() {
    clearConsole(); 
    std::cout << "Select Language / Изберете език:" << std::endl;
    std::cout << "  1. English (en) / Английски (en)" << std::endl;
    std::cout << "  2. Bulgarian (bg) / Български (bg)" << std::endl;
    std::cout << "Enter your choice / Въведете вашия избор: ";

    int choice;
    
    while (!(std::cin >> choice) || (choice < 1 || choice > 2)) {
        std::cout << RED << "Invalid choice. Please enter 1 or 2. / Невалиден избор. Моля, въведете 1 или 2." << RESET << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Enter your choice / Въведете вашия избор: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    
    if (choice == 1) {
        loadTranslations("en");
    } else { 
        loadTranslations("bg");
    }
    
    std::cout << GREEN << getTranslatedString("LANGUAGE_SET_SUCCESS") << RESET << std::endl;
}
