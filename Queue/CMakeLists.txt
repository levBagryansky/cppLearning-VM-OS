cmake_minimum_required(VERSION 3.16)
project(Queue)

set(CMAKE_CXX_STANDARD 14)

add_executable(Queue main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic  -g")

file(GLOB_RECURSE ALL_SOURCE_FILES QueueOnStack/*.cpp QueueOnStack/*.h)
file(GLOB_RECURSE ALL_CPP_FILES ./QueueOnStack/*.cpp)


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

add_subdirectory(QueueOnStack)
add_subdirectory(QueueOnList)

include_directories(QueueOnStack/include)
include_directories(QueueOnList/include)

if (ADD_TESTING)
    add_subdirectory(Google_test)
endif ()
