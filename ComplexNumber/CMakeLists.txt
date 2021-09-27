cmake_minimum_required(VERSION 3.20)
project(ComplexNumber)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ComplexNumber
        ComplexNum.cpp
        ComplexNum.h
        main.cpp)

