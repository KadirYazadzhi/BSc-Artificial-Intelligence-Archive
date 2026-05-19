/**
 * @brief Implementation of the Quicksort algorithm for sorting an array of Property structures.
 *
 * This file provides the concrete implementation for sorting property data
 * based on the `price` field, in either ascending or descending order.
 * Includes the main sort function `sortPropertiesArray` and its
 * helper functions: `swap`, `partition`, and the recursive `quickSort`.
 */

#include <iostream> // Although not used directly for output, sometimes useful for debugging

#include "sort.h"    // Header with sort function declarations
#include "structs.h" // Defines Property structure

using namespace std;

/**
 * @brief Public function to initiate sorting of a property array.
 *
 * This function serves as the entry point for sorting. Checks for base cases
 * (array of 0 or 1 element is already sorted) and then calls the recursive
 * `quickSort` function to perform the actual sorting operation. Currently,
 * properties are sorted based on their `price`.
 *
 * @param arr The array of `Property` structures to be sorted.
 * @param size The number of elements in the array.
 * @param sortAscending Boolean flag: `true` for ascending order, `false` for descending.
 */
void sortPropertiesArray(struct Property arr[], int size, bool sortAscending) {
    if (size <= 1) return; // Array of 0 or 1 element is already sorted.

    if (size < 50) quickSort(arr, 0, size - 1, sortAscending); // Calls recursive Quicksort function.
    else mergeSort(arr, 0, size - 1, sortAscending);
}