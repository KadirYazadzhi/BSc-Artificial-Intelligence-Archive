

#ifndef SORT_H
#define SORT_H

#include "structs.h" 


void sortPropertiesArray(struct Property arr[], int size, bool sortAscending);


int partition(struct Property arr[], int low, int high, bool sortAscending);


void quickSort(struct Property arr[], int low, int high, bool sortAscending);


void merge(struct Property arr[], int left, int mid, int right, bool sortAscending);


void mergeSort(struct Property arr[], int left, int right, bool sortAscending);


void swap(struct Property* a, struct Property* b);

#endif 