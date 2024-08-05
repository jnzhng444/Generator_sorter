cmake_minimum_required(VERSION 3.28)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled2 main.cpp
        paged_array.cpp
        paged_array.h
        sorting_algorithms.cpp
        sorting_algorithms.h
)

add_executable(generator generator.cpp
)
