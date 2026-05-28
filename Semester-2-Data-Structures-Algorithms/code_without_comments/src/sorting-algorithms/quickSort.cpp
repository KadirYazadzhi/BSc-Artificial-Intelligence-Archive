#include "sort.h"

void swap(Property& a, Property& b) {
    Property t = a;
    a = b;
    b = t;
}

int partition(Property arr[], int low, int high) {
    double pivot = arr[high].price;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].price < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(Property arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}