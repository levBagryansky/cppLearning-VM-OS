#ifndef STACK_IMPL_H
#define STACK_IMPL_H
#include <iostream>

template <class T>
class Stack {
   public:
    Stack();
    explicit Stack(size_t len);
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack();

    int getSize() const;
    bool isEmpty() const;
    void push(T value);
    void pop();
    T& top() const;
    void swap(Stack<T>& other);

    void changeFactor(double newFactor);

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;
    bool operator==(const Stack<T>& other) const;
    bool operator!=(const Stack<T>& other) const;

   private:
    double factor;
    size_t size_;
    size_t capacity_;
    T* data_;
};

template <class T>
Stack<T>::Stack() : factor(1.65), size_(0), capacity_(32), data_(new T[32]) {}

template <class T>
Stack<T>::Stack(size_t len)
    : factor(1.75), size_(0), capacity_(len), data_(new T[len]) {}

template <class T>
Stack<T>::Stack(const Stack& other)
    : factor(other.factor),
      size_(other.size_),
      capacity_(other.capacity_),
      data_(new T[other.capacity_]) {
    std::copy(other.data_, other.data_ + size_, data_);
}

template <class T>
Stack<T>::Stack(Stack&& other) noexcept
    : factor(other.factor),
      data_(other.data_),
      size_(other.size_),
      capacity_(other.capacity_) {
    other.data_ = nullptr;
}

template <class T>
Stack<T>::~Stack() {
    delete[] data_;
}

template <class T>
int Stack<T>::getSize() const {
    return size_;
}

template <class T>
bool Stack<T>::isEmpty() const {
    return size_ == 0;
}

template <class T>
void Stack<T>::push(T value) {
    if (size_ == capacity_) {
        T* new_data = new T[static_cast<int>(factor * capacity_)];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = static_cast<int>(factor * capacity_);
    }

    data_[size_] = value;
    size_++;
}

template <class T>
void Stack<T>::pop() {
    if (size_ == 0) {
        exit(1);
    }
    size_--;
}

template <class T>
T& Stack<T>::top() const {
    if (size_ == 0) {
        exit(2);
    }

    return data_[size_ - 1];
}

template <class T>
void Stack<T>::swap(Stack<T>& other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

template <class T>
void Stack<T>::changeFactor(double newFactor) {
    if (newFactor > 1) {
        factor = newFactor;
    } else {
        exit(1);
    }
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this == &other) {
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
    delete[] data_;
    data_ = new T[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
}

template <class T>
bool Stack<T>::operator==(const Stack<T>& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (uint64_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }

    return true;
}

template <class T>
bool Stack<T>::operator!=(const Stack<T>& other) const {
    return !(operator==(other));
}

#endif  // STACK_IMPL_H