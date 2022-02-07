cmake_minimum_required(VERSION 3.16)
project(HashTable)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(HashTable main.cpp)

if (ADD_CLANG_TIDY)
    message("Build with clang-tidy")
    set(CMAKE_CXX_CLANG_TIDY
            clang-tidy
            --format-style=file
            --header-filter=*.h
            )
endif ()

if (ADD_TESTING)
    add_subdirectory(Tests)
endif ()