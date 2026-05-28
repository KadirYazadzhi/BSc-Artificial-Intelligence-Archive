

#ifndef ADD_H
#define ADD_H

#include "structs.h"

void addSingleProperty(Node*& head);
void addMultipleProperties(Node*& head);


template <typename T>
T getValidNumericInput(const char* prompt);
void getValidStringInput(const char* prompt, char* buffer, size_t bufferSize);
void sanitizeString(char* str);

#endif 