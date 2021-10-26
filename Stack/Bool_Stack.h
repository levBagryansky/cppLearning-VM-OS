#ifndef STACK_H
#define STACK_H
#include "Stack_impl.h"
#include <iostream>

template<>
class Stack<bool> {
public:
    Stack();
    explicit Stack(size_t len);
    Stack(const Stack &other);
    Stack(Stack &&other);
    ~Stack();

    int getSize() const;
    bool isEmpty() const;
    void push(bool value);
    void pop();
    bool top() const;
    void swap(Stack<bool> &other);

    Stack& operator=(const Stack &other);
    Stack& operator=(Stack &&other);
    bool operator== (const Stack& other) const;
    bool operator!= (const Stack& other) const;

private:
    size_t size_;
    size_t capacity_;
    unsigned char *data_;
};

#endif // STACK_H
