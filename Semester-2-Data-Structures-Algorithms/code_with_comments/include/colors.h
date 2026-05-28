/**
 * @file colors.h
 * @brief Defines ANSI escape codes for coloring text in the console.
 *
 * These macros are used to add color to the terminal output, improving readability
 * and highlighting important information for the user.
 */

#ifndef COLOR_H
#define COLOR_H

#define RESET   "\033[0m"  ///< Resets text color and formatting to default.
#define RED     "\033[31m" ///< Sets text color to red.
#define GREEN   "\033[32m" ///< Sets text color to green.
#define YELLOW  "\033[33m" ///< Sets text color to yellow.
#define CYAN    "\033[36m" ///< Sets text color to cyan.

#endif