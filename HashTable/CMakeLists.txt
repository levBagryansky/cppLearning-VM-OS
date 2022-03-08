cmake_minimum_required(VERSION 3.16)
project(HashTable)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread")

include_directories(include)
include_directories(Tests)

add_executable(HashTable main.cpp)
#target_include_directories(HashTable INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if (ADD_CLANG_TIDY)
    message("Build with clang-tidy")
    set(CMAKE_CXX_CLANG_TIDY
            clang-tidy
            --format-style=file
            --header-filter=*.h)
endif ()

add_subdirectory(Tests)


if (ADD_TESTING)
    add_subdirectory(Tests)
endif ()
