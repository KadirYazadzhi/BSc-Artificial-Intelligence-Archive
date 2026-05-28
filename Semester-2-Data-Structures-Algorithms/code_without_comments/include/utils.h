

#ifndef UTILS_H
#define UTILS_H


void clearConsole();


void printBanner();


void ensureDirectoryExists(const char* path);


int getMenuChoice(int min, int max);


bool getConfirmation(const char* prompt);


bool stringsEqualIgnoreCase(const char* s1, const char* s2);

#endif 