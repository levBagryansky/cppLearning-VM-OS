cmake_minimum_required(VERSION 3.16)
project(LocalityResearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O0")

add_custom_target(
        clang-format
        COMMAND clang-format
        -i
        ${ALL_SOURCE_FILES}
)

if (ADD_CLANG_TIDY)
    message("Build with clang-tidy")
    set(CMAKE_CXX_CLANG_TIDY
            clang-tidy
            --format-style=file
            --header-filter=*.h
            )
endif ()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(benchmark REQUIRED)

add_executable(Example1 example1.cpp)
target_link_libraries(Example1 benchmark::benchmark)

add_executable(Example2 example2.cpp)
target_link_libraries(Example2 benchmark::benchmark)