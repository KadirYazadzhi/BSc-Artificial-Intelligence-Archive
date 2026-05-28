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
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝   ╚═╝
        Информационна система 'Агенция за недвижими имоти' - DSA Edition
  )" << endl;
}

int getMenuChoice(int min, int max) {
    int choice;
    while (true) {
        cout << CYAN << getTranslatedString("ENTER_YOUR_CHOICE") << RESET;
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice >= min && choice <= max) {
                return choice;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << RED << getTranslatedString("INVALID_OPTION") << RESET << endl;
    }
}

bool getConfirmation(const char* prompt) {
    char option;
    cout << YELLOW << prompt << " (y/n): " << RESET;
    cin >> option;
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