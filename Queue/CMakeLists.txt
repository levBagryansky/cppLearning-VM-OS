cmake_minimum_required(VERSION 3.16)
project(Queue)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB_RECURSE ALL_SOURCE_FILES QueueOnStack/*.cpp QueueOnStack/*.h)
file(GLOB_RECURSE ALL_CPP_FILES ./Stack/*.cpp)
include_directories(Stack/include/)

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

include_directories(QueueOnStack/include)
include_directories(QueueOnList/include)

add_subdirectory(Tests)

if (ADD_BENCHMARK)
    add_subdirectory(Benchmark)
endif ()
