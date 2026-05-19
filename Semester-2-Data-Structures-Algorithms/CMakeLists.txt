cmake_minimum_required(VERSION 3.10)
project(Solution)

set(CMAKE_CXX_STANDARD 14)

add_executable(Solution
    src/add.cpp
    src/display.cpp
    src/main.cpp
    src/reports.cpp
    src/search.cpp
    src/sort.cpp
    src/structs.cpp
    src/delete.cpp
    src/menu.cpp
    src/utils.cpp
    src/localization.cpp
    src/test_data.cpp
    src/sorting-algorithms/quickSort.cpp
    src/sorting-algorithms/mergeSort.cpp
    src/sorting-algorithms/bubbleSort.cpp
    src/sorting-algorithms/selectionSort.cpp
)

target_include_directories(Solution PRIVATE include)
target_compile_definitions(Solution PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")