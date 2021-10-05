#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

template <typename T>

class Stack{
public:
    Stack(int len = 32);
    Stack(const Stack& other);
    Stack(Stack&& other);
    ~Stack();
    void push(int x);
    int pop();
    int peek() const;
    int getSize() const;

    Stack& operator= (const Stack& other);
    Stack& operator= (Stack&& other);
    friend std::ostream& operator<< (std::ostream& os, const Stack& s);

private:
    T* data_;
    int size_;
    int capacity_;
};

#endif