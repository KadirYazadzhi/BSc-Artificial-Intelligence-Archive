

#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <string> 


#define MAX_TRANSLATIONS 500

#define MAX_TRANSLATION_STRING_LENGTH 256


struct TranslationEntry {
    char key[MAX_TRANSLATION_STRING_LENGTH];
    char value[MAX_TRANSLATION_STRING_LENGTH];
};


extern TranslationEntry g_translations[MAX_TRANSLATIONS];
extern int g_translationCount; 
extern std::string currentLanguage; 


void loadTranslations(const std::string& langCode);


std::string getTranslatedString(const std::string& key);


void selectLanguage();

#endif 