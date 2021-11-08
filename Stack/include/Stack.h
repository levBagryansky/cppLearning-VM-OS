#ifndef STACK_H
#define STACK_H
#include <iostream>

#include "Stack-impl.h"

template <>
class Stack<bool> {
   public:
    Stack();
    explicit Stack(size_t len);
    Stack(const Stack &other);
    Stack(Stack &&other) noexcept;
    ~Stack();

    size_t getSize() const;
    bool isEmpty() const;
    void push(bool value);
    void pop();
    bool top() const;
    void swap(Stack<bool> &other);

    Stack &operator=(const Stack &other);
    Stack &operator=(Stack &&other) noexcept;
    bool operator==(const Stack &other) const;

   private:
    size_t size_;
    size_t capacity_;
    unsigned char *data_;
};

#endif  // STACK_H
