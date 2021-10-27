cmake_minimum_required(VERSION 3.20)
project(Stack)

set(CMAKE_CXX_CLANG_TIDY)

include_directories(include)

add_executable(Stack main.cpp BoolStack.cpp)

add_subdirectory(Google_test)

add_subdirectory(Google_benchmark)
