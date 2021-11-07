#ifndef STACK_H
#define STACK_H
#include <iostream>

#include "Stack-impl.h"

template <>
class BoolStack<bool> {
   public:
    BoolStack();
    explicit BoolStack(size_t len);
    BoolStack(const BoolStack &other);
    BoolStack(BoolStack &&other) noexcept;
    ~BoolStack();

    size_t getSize() const;
    bool isEmpty() const;
    void push(bool value);
    void pop();
    bool top() const;
    void swap(BoolStack<bool> &other);

    BoolStack &operator=(const BoolStack &other);
    BoolStack &operator=(BoolStack &&other) noexcept;
    bool operator==(const BoolStack &other) const;
    bool operator!=(const BoolStack &other) const;

   private:
    size_t size_;
    size_t capacity_;
    unsigned char *data_;
};

#endif  // STACK_H
