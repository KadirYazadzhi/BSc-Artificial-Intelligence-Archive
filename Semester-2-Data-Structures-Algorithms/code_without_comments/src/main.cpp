

#include "structs.h"
#include "utils.h"
#include "menu.h"
#include "localization.h"
#include "test_data.h"


int main() {
    Node* head = nullptr; 

    
    loadTranslations("bg");

    
    printBanner();

    
    selectLanguage();

    
    
    if (head == nullptr) {
        if (getConfirmation(getTranslatedString("GENERATE_TEST_DATA_PROMPT").c_str())) {
            generateTestProperties(head);
        }
    }

    
    mainMenu(head);

    
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}