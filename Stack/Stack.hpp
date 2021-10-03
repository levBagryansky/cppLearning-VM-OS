#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

class Stack{
    int* arr_;
    int size_;
    int capacity_;

public:
    friend std::ostream& operator<< (std::ostream& os, const Stack& s);
};

#endif