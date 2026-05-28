

#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>


#define MAX_PROPERTIES 100


enum Status { SOLD, RESERVED, AVAILABLE };


std::string getStatusString(enum Status status);


struct Property {
    int refNumber;      
    char broker[50];    
    char type[50];      
    char area[50];      
    char exposition[20];
    double price;       
    double totalArea;   
    int rooms;          
    int floor;          
    enum Status status; 
};

#endif 