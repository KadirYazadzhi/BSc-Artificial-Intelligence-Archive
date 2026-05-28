#include <iostream> // Necessary for I/O operations
#include "sort.h"    // Necessary for sort function declarations
#include "structs.h" // Defines Property structure

using namespace std;

/**
 * @brief Merges two subarrays of arr[].
 *
 * The first subarray is arr[left..mid].
 * The second subarray is arr[mid+1..right].
 * This function is used by Merge Sort to combine two sorted subarrays
 * into a single sorted array. Sorting is performed based on the `price` field.
 *
 * @param arr The array of `Property` structures.
 * @param left The starting index of the first subarray.
 * @param mid The ending index of the first subarray.
 * @param right The ending index of the second subarray.
 * @param sortAscending Boolean flag indicating sort order (`true` for ascending).
 */
void merge(struct Property arr[], int left, int mid, int right, bool sortAscending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    // Dynamic memory is used since size is not known at compile time
    Property* L = new Property[n1];
    Property* R = new Property[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        bool condition;

        // Determine condition based on sort order
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

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free allocated memory for temporary arrays
    delete[] L;
    delete[] R;
}

/**
 * @brief Recursive implementation of the Merge Sort algorithm.
 *
 * This function divides the array into two halves, recursively calls itself for the two halves,
 * and then merges the two sorted halves.
 *
 * @param arr The array of `Property` structures to be sorted.
 * @param left The starting index of the subarray to sort.
 * @param right The ending index of the subarray to sort.
 * @param sortAscending Boolean flag indicating sort order.
 */
void mergeSort(struct Property arr[], int left, int right, bool sortAscending) {
    if (left >= right) return; // Base case: subarray has 0 or 1 elements

    int mid = left + (right - left) / 2; // Find middle to avoid overflow

    mergeSort(arr, left, mid, sortAscending);      // Sort first half
    mergeSort(arr, mid + 1, right, sortAscending); // Sort second half

    merge(arr, left, mid, right, sortAscending);   // Merge the sorted halves
}