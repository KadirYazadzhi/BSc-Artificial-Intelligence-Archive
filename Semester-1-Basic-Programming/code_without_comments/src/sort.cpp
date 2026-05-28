

#include <iostream> 

#include "sort.h"    
#include "structs.h" 

using namespace std;


void sortPropertiesArray(struct Property arr[], int size, bool sortAscending) {
    if (size <= 1) return; 

    if (size < 50) quickSort(arr, 0, size - 1, sortAscending); 
    else mergeSort(arr, 0, size - 1, sortAscending);
}