

#include <iostream>
#include <limits>      
#include <string>      
#include <cctype>      
#include <cstdlib>     
#include "utils.h"
#include "colors.h"    
#include "localization.h" 

using namespace std;


void clearConsole() {
  
  
  cout << "\033[2J\033[1;1H";
}


void printBanner() {
  cout << R"(
██████╗ ███████╗ █████╗ ██╗         ███████╗███████╗████████╗ █████╗ ████████╗███████╗     █████╗  ██████╗ ███████╗███╗   ██╗ ██████╗██╗   ██╗
██╔══██╗██╔════╝██╔══██╗██║         ██╔════╝██╔════╝╚══██╔══╝██╔══██╗╚══██╔╝╝ ██╔════╝    ██╔══██╗██╔════╝ ██╔════╝████╗  ██║██╔════╝╚██╗ ██╔╝
██████╔╝█████╗  ███████║██║         █████╗  ███████╗   ██║   ███████║   ██║   █████╗      ███████║██║  ███╗█████╗  ██╔██╗ ██║██║      ╚████╔╝
██╔══██╗██╔══╝  ██╔══██║██║         ██╔══╝  ╚════██║   ██║   ██╔══██║   ██║   ██╔══╝      ██╔══██║██║   ██║██╔══╝  ██║╚██╗██║██║       ╚██╔╝
██║  ██║███████╗██║  ██║███████╗    ███████╗███████║   ██║   ██║  ██║   ██║   ███████╗    ██║  ██║╚██████╔╝███████╗██║ ╚████║╚██████╗   ██║
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝  ╚═╝
        Информационна система 'Агенция за недвижими имоти'                                                     realestateagency - @kadir_
  )"
  << endl;
}


void ensureDirectoryExists(const char* path) {
    string command = "mkdir -p "; 
    command += path;
    system(command.c_str()); 
}


int getMenuChoice(int min, int max) {
    int choice;
    cout << CYAN << getTranslatedString("ENTER_YOUR_CHOICE") << RESET; 

    
    if (!cin) {
        cin.clear(); 
        choice = -1; 
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    
    if (choice < min || choice > max) {
        return -1; 
    }

    return choice;
}


bool getConfirmation(const char* prompt) {
    char option;
    cout << YELLOW << prompt << RESET; 
    cin >> option;

    
    if (!cin) {
        cin.clear(); 
    }

    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return (tolower(option) == 'y');
}


bool stringsEqualIgnoreCase(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return false;
        }
        s1++;
        s2++;
    }
    
    return (*s1 == *s2);
}
