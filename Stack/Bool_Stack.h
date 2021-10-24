#ifndef STACK_H
#define STACK_H
#include "Stack_impl.h"
#include <iostream>

template<>
class Stack<bool> {
public:
    Stack(int len = 32);
    Stack(const Stack &other);
    Stack(Stack &&other);
    ~Stack();

    int getSize() const;
    bool isEmpty() const;
    void push(bool x);
    void pop();
    bool top() const;
    void swap(Stack<bool> &other);

    Stack& operator=(const Stack &other);
    Stack& operator=(Stack &&other);
    bool operator== (const Stack& other) const;
    bool operator!= (const Stack& other) const;

    friend std::ostream& operator<<(std::ostream &os, Stack &s);

private:
    int size_;
    int capacity_;
    unsigned char *data_;
};

#endif // STACK_H
