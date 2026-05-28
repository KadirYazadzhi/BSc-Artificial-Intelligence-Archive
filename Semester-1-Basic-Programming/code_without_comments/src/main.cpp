

#include "structs.h"       
#include "file.h"          
#include "utils.h"         
#include "menu.h"          
#include "localization.h"  
#include "test_data.h"     


int main() {
  Property properties[MAX_PROPERTIES]; 
  int propertyCount = 0; 

  
  loadTranslations("bg");

  
  printBanner();

  
  selectLanguage();

  
  
  loadFromSyncTextFile(properties, propertyCount);

  
  if (propertyCount == 0) {
      if (getConfirmation(getTranslatedString("GENERATE_TEST_DATA_PROMPT").c_str())) {
          generateTestProperties(properties, propertyCount);
      }
  }

  
  
  mainMenu(properties, propertyCount);

  return 0; 
}