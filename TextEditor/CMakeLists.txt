cmake_minimum_required(VERSION 3.16)
project(TextEditor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")

include_directories(include)
file(GLOB_RECURSE SOURCE_FILES ./src/*.cpp)
include_directories(Tests)

if (ADD_CLANG_TIDY)
    message("Build with clang-tidy")
    set(CMAKE_CXX_CLANG_TIDY
            clang-tidy
            --format-style=file
            --header-filter=*.h)
endif ()

add_custom_target(
        clang-format
        COMMAND clang-format
        -i
        ${SOURCE_FILES}
)

add_subdirectory(Tests)

add_subdirectory(Benchmark)
