#include <iostream> // Although not used directly for output, sometimes useful for debugging

#include "sort.h"    // Header with sort function declarations
#include "structs.h" // Defines Property structure

using namespace std;

/**
 * @brief Swaps two `Property` structures in memory.
 *
 * This helper function is used by the sorting algorithm to efficiently swap
 * the positions of two elements.
 *
 * @param a Pointer to the first `Property` structure.
 * @param b Pointer to the second `Property` structure.
 */
void swap(struct Property* a, struct Property* b) {
    Property temp = *a; // Store value of 'a' temporarily.
    *a = *b;            // Assign value of 'b' to 'a'.
    *b = temp;          // Assign temporary value (original 'a') to 'b'.
}

/**
 * @brief Partitions a subarray around a pivot element as part of the Quicksort algorithm.
 *
 * This function selects the last element as the pivot. It rearranges elements
 * in the subarray such that all elements satisfying the sort condition (e.g.
 * smaller than pivot for ascending sort) come before the pivot, and all elements
 * that do not satisfy the condition come after it. Returns the final position of the pivot.
 *
 * @param arr The array of `Property` structures to be partitioned.
 * @param low The starting index of the subarray to partition.
 * @param high The ending index of the subarray to partition.
 * @param sortAscending Boolean flag indicating sort order (`true` for ascending).
 * @return The index of the pivot element after partitioning.
 */
int partition(struct Property arr[], int low, int high, bool sortAscending) {
    double pivotPrice = arr[high].price; // Select price of last element as pivot.
    int i = (low - 1); // Index of smaller element.

    // Iterate through subarray from 'low' to 'high - 1'.
    for (int j = low; j <= high - 1; j++) {
        bool condition;

        // Swap condition depends on sort order.
        if (sortAscending) {
            condition = (arr[j].price < pivotPrice); // For ascending: current element price < pivot price.
        } else {
            condition = (arr[j].price > pivotPrice); // For descending: current element price > pivot price.
        }

        // If current element satisfies condition, swap it with element at (i+1).
        if (condition) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]); // Place pivot element in its correct sorted position.
    return (i + 1); // Return partition index (final position of pivot).
}

/**
 * @brief Recursive implementation of the Quicksort algorithm.
 *
 * This function sorts a subarray of `Property` structures in place. It works by
 * partitioning the array around a pivot element and then recursively calling
 * itself for the subarrays before and after the pivot. The base case of recursion
 * is when the subarray has 0 or 1 elements.
 *
 * @param arr The array of `Property` structures to be sorted.
 * @param low The starting index of the subarray.
 * @param high The ending index of the subarray.
 * @param sortAscending Boolean flag indicating sort order.
 */
void quickSort(struct Property arr[], int low, int high, bool sortAscending) {
    if (low >= high) return; // Base case: If subarray has 0 or 1 elements, it is already sorted.

    // Find partition index such that elements are correctly positioned relative to pivot.
    int pi = partition(arr, low, high, sortAscending);

    // Recursively sort the two subarrays.
    quickSort(arr, low, pi - 1, sortAscending);   // Sort elements before pivot.
    quickSort(arr, pi + 1, high, sortAscending); // Sort elements after pivot.
}