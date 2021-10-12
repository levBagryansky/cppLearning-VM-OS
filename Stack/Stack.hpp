#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

template<class T>
class Stack {
public:
    Stack(int len = 32);
    Stack(const Stack &other);
    Stack(Stack &&other);
    ~Stack();

    int getSize() const;
    bool isEmpty() const;
    void push(T x);
    T pop();
    T top() const;
    void swap(Stack<T> &other);

    Stack& operator=(const Stack &other);
    Stack& operator=(Stack &&other);
    bool operator== (const Stack<T>& other) const;
    bool operator!= (const Stack<T>& other) const;

    template<class U>
    friend std::ostream& operator<<(std::ostream &os, Stack<U> &s);

private:
    int size_;
    int capacity_;
    T *data_;
};

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
    bool pop();
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

#endif // STACK_HPP
