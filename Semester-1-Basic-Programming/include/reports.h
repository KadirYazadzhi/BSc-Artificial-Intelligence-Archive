/**
 * @file reports.h
 * @brief Declares functions for generating various analytical reports on property data.
 *
 * Includes functionality for identifying most expensive properties, calculating
 * average prices in specific areas, and determining sales percentages per broker,
 * providing valuable insights into the real estate market.
 */

#ifndef REPORTS_H
#define REPORTS_H

#include "structs.h" // Necessary for Property type

/**
 * @brief Finds and displays the most expensive property in a user-specified area.
 * @param properties Array of Property structures to analyze.
 * @param propertyCount The number of properties in the array.
 *
 * This report helps identify premium listings in specific geographical locations.
 */
void mostExpensiveInArea(const Property properties[], int propertyCount);

/**
 * @brief Calculates and displays the average price of properties in a user-specified area.
 * @param properties Array of Property structures to analyze.
 * @param propertyCount The number of properties in the array.
 *
 * Provides market information by averaging prices, useful for pricing strategies and buyer information.
 */
void averagePriceInArea(const Property properties[], int propertyCount);

/**
 * @brief Calculates and displays the percentage of properties sold by each broker.
 * @param properties Array of Property structures to analyze.
 * @param propertyCount The number of properties in the array.
 *
 * This report offers performance metrics for individual brokers, highlighting sales efficiency.
 */
void soldPercentagePerBroker(const Property properties[], int propertyCount);

#endif //REPORTS_H