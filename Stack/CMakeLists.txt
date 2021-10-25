cmake_minimum_required(VERSION 3.20)
project(Stack)

set(CMAKE_CXX_CLANG_TIDY)

add_executable(Stack main.cpp Bool_Stack.cpp)

add_subdirectory(Google_test)

add_subdirectory(Google_benchmark)

