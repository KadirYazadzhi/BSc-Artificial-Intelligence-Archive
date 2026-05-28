#include <iostream> 
#include "sort.h"    
#include "structs.h" 

using namespace std;


void merge(struct Property arr[], int left, int mid, int right, bool sortAscending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    
    
    Property* L = new Property[n1];
    Property* R = new Property[n2];

    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2) {
        bool condition;

        
        if (sortAscending) condition = (L[i].price <= R[j].price);
        else condition = (L[i].price >= R[j].price);

        if (condition) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    
    delete[] L;
    delete[] R;
}


void mergeSort(struct Property arr[], int left, int right, bool sortAscending) {
    if (left >= right) return; 

    int mid = left + (right - left) / 2; 

    mergeSort(arr, left, mid, sortAscending);      
    mergeSort(arr, mid + 1, right, sortAscending); 

    merge(arr, left, mid, right, sortAscending);   
}