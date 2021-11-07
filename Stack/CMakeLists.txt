cmake_minimum_required(VERSION 3.16)

project(Stack)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(${PROJECT_NAME} main.cpp)

add_custom_target(run_${PROJECT_NAME}
        COMMENT "Running main"
        COMMAND ./${PROJECT_NAME})

add_dependencies(run_${PROJECT_NAME} ${PROJECT_NAME})

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -header-filter=*;
        -checks=*;
        )

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
add_custom_target(
        clang-format
        COMMAND clang-format
        -i
        ${ALL_SOURCE_FILES}
)
