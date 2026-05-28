

#include "structs.h" 
#include "localization.h" 


std::string getStatusString(enum Status status) {
    switch (status) {
        case SOLD:
            
            return getTranslatedString("STATUS_SOLD_TEXT");
        case RESERVED:
            
            return getTranslatedString("STATUS_RESERVED_TEXT");
        case AVAILABLE:
            
            return getTranslatedString("STATUS_AVAILABLE_TEXT");
        default:
            
            return getTranslatedString("STATUS_UNKNOWN_TEXT");
    }
}
