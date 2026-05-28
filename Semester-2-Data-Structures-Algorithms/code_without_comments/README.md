# Real Estate Agency Information System

```
██████╗ ███████╗ █████╗ ██╗         ███████╗███████╗████████╗ █████╗ ████████╗███████╗     █████╗  ██████╗ ███████╗███╗   ██╗ ██████╗██╗   ██╗
██╔══██╗██╔════╝██╔══██╗██║         ██╔════╝██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██╔════╝    ██╔══██╗██╔════╝ ██╔════╝████╗  ██║██╔════╝╚██╗ ██╔╝
██████╔╝█████╗  ███████║██║         █████╗  ███████╗   ██║   ███████║   ██║   █████╗      ███████║██║  ███╗█████╗  ██╔██╗ ██║██║      ╚████╔╝
██╔══██╗██╔══╝  ██╔══██║██║         ██╔══╝  ╚════██║   ██║   ██╔══██║   ██║   ██╔══╝      ██╔══██║██║   ██║██╔══╝  ██║╚██╗██║██║       ╚██╔╝
██║  ██║███████╗██║  ██║███████╗    ███████╗███████║   ██║   ██║  ██║   ██║   ███████╗    ██║  ██║╚██████╔╝███████╗██║ ╚████║╚██████╗   ██║
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝   ╚═╝
        Информационна система 'Агенция за недвижими имоти' - DSA Edition               realestateagency - @kadir_
```

## 1. Project Goal

The primary goal of this project is to develop a console-based information system for a real estate agency, specifically refactored to demonstrate advanced **Algorithms and Data Structures (DSA)**. The system manages a portfolio of properties using a dynamic linked list and implements various sorting and search algorithms as part of a university-level semester assignment.

This project demonstrates core programming concepts in C++, including modular programming, linked lists, recursive binary search, and hybrid sorting techniques.

## 2. Requirements

The application is built to meet the following specifications from the assignment PDF:

### Base Task

*   **A: Main Menu:** A user-friendly main menu to navigate through the system's functions.
*   **B: Add/Remove Property:**
    *   Uses a **Linked List** instead of an array.
    *   Functionality to add single or multiple properties.
    *   Ability to remove properties from the list.
*   **C: Display Properties:** Display properties in a well-formatted manner.
*   **D: Search (Binary):**
    *   Recursive binary search by reference number.
    *   Requires conversion to a sorted array for the search process.
*   **E: Sort Properties:**
    *   Sort the first 10 elements of the list using **Quicksort** (Exchange Sorts).
    *   Sort the entire linked list using **Bubble Sort** by price.
*   **F: File Management:** (Omitted as per new requirement "ОТПАДА").

### First Extension

*   **G: Specialized Reports & Sorting:**
    *   Extract properties with the largest area and sort them using **Selection Sort**.
    *   Extract sold properties and sort them using **Merge Sort**.

## 3. Project Structure

The project is organized into a `src` directory for source files, an `include` directory for header files, and a `lang` directory for language files.

```
/
|-- /src
|   |-- sorting-algorithms/
|   |   |-- bubbleSort.cpp
|   |   |-- quickSort.cpp
|   |   |-- mergeSort.cpp
|   |   |-- selectionSort.cpp
|   |-- main.cpp
|   |-- add.cpp
|   |-- delete.cpp
|   |-- ...
|-- /include
|   |-- structs.h
|   |-- ...
|-- /lang
|   |-- en.txt
|   |-- bg.txt
```

## 4. Implementation Details

### Data Structures

The core data structure is the `Property` struct, defined in `include/structs.h`. It is managed via a `Node` struct to form a **Dynamic Linked List**.

### Core Logic and Techniques

*   **Modular Programming:** The code is split into multiple files, separating concerns like menu management, search, and sorting.
*   **Dynamic List Management:** Properties are added at the head of the list, and deletion handles both head and middle/tail nodes safely.
*   **Sorting Algorithms:**
    1.  **Bubble Sort:** Applied directly to the linked list nodes.
    2.  **Quicksort:** Used for fast sorting of the first 10 elements in a temporary array.
    3.  **Selection Sort:** Used for sorting report data (area-based).
    4.  **Merge Sort:** Used for sorting sold properties data.
*   **Recursive Binary Search:** Implemented as a recursive function to find properties by their unique reference number.
*   **User Interface:** Enhanced with colors and localized in both Bulgarian and English.

## 5. File and Function Breakdown

### `src/main.cpp`
*   **Purpose:** Entry point, handles language selection and main menu orchestration.

### `src/menu.cpp`
*   **Purpose:** Manages the console UI and sub-menus.

### `src/add.cpp` / `src/delete.cpp`
*   **Purpose:** Logic for linked list insertion and node removal.

### `src/search.cpp`
*   **Purpose:** Implements recursive binary search by converting the list to a temporary sorted vector.

### `src/sort.cpp`
*   **Purpose:** Entry point for sorting operations (First 10 vs Full List).

### `src/sorting-algorithms/`
*   **Purpose:** Contains individual implementations of Bubble Sort, Quicksort, Merge Sort, and Selection Sort.

### `src/reports.cpp`
*   **Purpose:** Generates sorted reports for largest area and sold properties.

### `src/localization.cpp`
*   **Purpose:** Multi-language support through key-value translation files.

## 6. Project Statistics

*   **Total Lines of Code:** 1422 (Excluding empty lines and comments)

| File | Lines |
| :--- | :--- |
| `src/add.cpp` | 79 |
| `src/delete.cpp` | 46 |
| `src/display.cpp` | 93 |
| `src/localization.cpp` | 152 |
| `src/main.cpp` | 45 |
| `src/menu.cpp` | 118 |
| `src/reports.cpp` | 102 |
| `src/search.cpp` | 52 |
| `src/sort.cpp` | 40 |
| `src/structs.cpp` | 41 |
| `src/test_data.cpp` | 47 |
| `src/utils.cpp` | 61 |
| `src/sorting-algorithms/bubbleSort.cpp` | 25 |
| `src/sorting-algorithms/mergeSort.cpp` | 44 |
| `src/sorting-algorithms/quickSort.cpp` | 28 |
| `src/sorting-algorithms/selectionSort.cpp` | 14 |
| `include/add.h` | 19 |
| `include/colors.h` | 17 |
| `include/delete.h` | 13 |
| `include/display.h` | 16 |
| `include/localization.h` | 61 |
| `include/menu.h` | 18 |
| `include/reports.h` | 13 |
| `include/search.h` | 12 |
| `include/sort.h` | 22 |
| `include/structs.h` | 44 |
| `include/test_data.h` | 16 |
| `include/utils.h` | 64 |
