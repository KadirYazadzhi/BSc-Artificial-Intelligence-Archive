cmake_minimum_required(VERSION 3.25)
project(Solution)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

include_directories(include)

add_executable(Solution
    src/add.cpp
    src/display.cpp
    src/file.cpp
    src/main.cpp
    src/reports.cpp
    src/search.cpp
    src/sort.cpp
    src/structs.cpp
    src/update.cpp
    src/delete.cpp
    src/menu.cpp
    src/utils.cpp
    src/localization.cpp
    src/test_data.cpp
        src/sorting-algorithms/quickSort.cpp
        src/sorting-algorithms/mergeSort.cpp
        include/test_data.h
)
