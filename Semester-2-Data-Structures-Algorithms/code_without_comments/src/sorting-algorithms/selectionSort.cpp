#include "sort.h"

void selectionSort(Property arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].totalArea > arr[min_idx].totalArea) 
                min_idx = j;
        }
        Property temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}