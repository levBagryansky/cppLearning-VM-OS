cmake_minimum_required(VERSION 3.16)

project(Stack)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp include/*.h)

add_custom_target(
        clang-format
        COMMAND clang-format
        -i
        ${ALL_SOURCE_FILES}
)

include_directories(include)

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -header-filter=*;
        -checks=*;
        )

if (ADD_TESTING)
    add_subdirectory(Google_test)
endif ()

if (ADD_BENCHMARK)
    add_subdirectory(Google_benchmark)
endif ()
