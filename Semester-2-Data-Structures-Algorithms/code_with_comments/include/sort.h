/**
 * @file sort.h
 * @brief Declares sorting algorithms for properties.
 */

#ifndef SORT_H
#define SORT_H

#include "structs.h"

// Linked List Sorting
void bubbleSort(Node* head);

// Array Sorting
void quickSort(Property arr[], int low, int high);
void selectionSort(Property arr[], int n);
void mergeSort(Property arr[], int l, int r);

// Orchestration
void sortFirstTenInArray(Node* head);
void sortLinkedList(Node* head);

#endif // SORT_H