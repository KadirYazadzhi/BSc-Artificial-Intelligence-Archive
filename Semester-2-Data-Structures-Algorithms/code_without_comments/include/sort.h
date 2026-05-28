

#ifndef SORT_H
#define SORT_H

#include "structs.h"


void bubbleSort(Node* head);


void quickSort(Property arr[], int low, int high);
void selectionSort(Property arr[], int n);
void mergeSort(Property arr[], int l, int r);


void sortFirstTenInArray(Node* head);
void sortLinkedList(Node* head);

#endif 