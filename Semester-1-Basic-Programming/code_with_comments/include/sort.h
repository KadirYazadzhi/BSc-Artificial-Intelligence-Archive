/**
 * @file sort.h
 * @brief Declares functions for sorting property arrays.
 *
 * Provides implementation of the QuickSort algorithm adapted for `Property` structures,
 * allowing properties to be sorted based on various criteria (e.g., price, area)
 * in ascending or descending order.
 */

#ifndef SORT_H
#define SORT_H

#include "structs.h" // Necessary for Property type

/**
 * @brief Sorts an array of Property structures using the QuickSort algorithm.
 * @param arr The array of Property structures to be sorted.
 * @param size The number of elements in the array.
 * @param sortAscending Boolean flag: true for ascending order, false for descending.
 *
 * This is the main entry point for sorting properties. Currently sorts by price.
 * The implementation internally calls `quickSort` after initializing the sorting process.
 */
void sortPropertiesArray(struct Property arr[], int size, bool sortAscending);

/**
 * @brief Partitions the array around a pivot element.
 * @param arr The array to be partitioned.
 * @param low The starting index of the subarray to partition.
 * @param high The ending index of the subarray to partition.
 * @param sortAscending Boolean flag indicating sort order (true for ascending).
 * @return The index of the pivot element after partitioning.
 *
 * This is a helper function for the QuickSort algorithm that rearranges elements
 * so that elements smaller (or larger, depending on sort order) than the pivot
 * come before (or after) it.
 */
int partition(struct Property arr[], int low, int high, bool sortAscending);

/**
 * @brief Implements the QuickSort algorithm for sorting an array of Property structures.
 * @param arr The array of Property structures to be sorted.
 * @param low The starting index of the subarray to sort.
 * @param high The ending index of the subarray to sort.
 * @param sortAscending Boolean flag indicating sort order (true for ascending).
 *
 * This recursive function efficiently sorts properties in place based on
 * the selected criterion (currently price).
 */
void quickSort(struct Property arr[], int low, int high, bool sortAscending);

/**
 * @brief Merges two sorted subarrays into one.
 * @param arr The array of Property structures.
 * @param left Starting index.
 * @param mid Middle index.
 * @param right Ending index.
 * @param sortAscending Sort order.
 */
void merge(struct Property arr[], int left, int mid, int right, bool sortAscending);

/**
 * @brief Implements the Merge Sort algorithm.
 * @param arr The array to sort.
 * @param left Starting index.
 * @param right Ending index.
 * @param sortAscending Sort order.
 */
void mergeSort(struct Property arr[], int left, int right, bool sortAscending);

/**
 * @brief Swaps two Property structures.
 * @param a Pointer to the first Property structure.
 * @param b Pointer to the second Property structure.
 *
 * Helper function used by the sorting algorithm to swap element positions.
 */
void swap(struct Property* a, struct Property* b);

#endif //SORT_H