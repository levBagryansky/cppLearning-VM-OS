#include "Stack.h"
#include <cmath>

const int BYTES_IN_CHAR = 8;
const int START_CAPACITY = 32;


Stack<bool>::Stack()
    : size_(0), capacity_((START_CAPACITY + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR), data_(new unsigned char[capacity_]) {}

Stack<bool>::Stack(size_t len)
    : size_(0), capacity_((len + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR), data_(new unsigned char[capacity_]) {}

Stack<bool>::Stack(const Stack &other)
    : size_(other.size_),
      capacity_(other.capacity_),
      data_(new unsigned char[(other.capacity_ + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR]) {
    std::copy(other.data_, other.data_ + (size_ + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR, data_);
}

Stack<bool>::Stack(Stack &&other) noexcept
    : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
    other.data_ = nullptr;
}

Stack<bool>::~Stack() { delete[] data_; }

size_t Stack<bool>::getSize() const { return size_; }

bool Stack<bool>::isEmpty() const { return size_ == 0; }

void Stack<bool>::push(bool value) {
    if (size_ == capacity_) {
        auto *new_data = new unsigned char[2 * ((capacity_ + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR)];
        std::copy(data_, data_ + (size_ + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = 2 * ((capacity_ + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR) * BYTES_IN_CHAR;
    }

    auto i = size_ % BYTES_IN_CHAR;
    data_[size_ / BYTES_IN_CHAR] =
        ((data_[size_ / BYTES_IN_CHAR] & (~(1U << i))) + (static_cast<unsigned int>(value) << i));
    size_++;
}

void Stack<bool>::pop() {
    if (size_ == 0) {
        exit(1);
    }
    size_--;
}

bool Stack<bool>::top() const {
    if (size_ == 0) {
        exit(2);
    }

    unsigned char contain_elem = data_[(size_ - 1) / BYTES_IN_CHAR];
    contain_elem = contain_elem >> ((size_ - 1) % BYTES_IN_CHAR);
    contain_elem &= 1U;
    return contain_elem == 1;
}

void Stack<bool>::swap(Stack<bool> &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

Stack<bool> &Stack<bool>::operator=(const Stack<bool> &other) {
    if (this == &other) {
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;

    delete[] data_;
    data_ = new unsigned char[(capacity_ + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR];
    std::copy(other.data_, other.data_ + (size_ + BYTES_IN_CHAR - 1) / BYTES_IN_CHAR, data_);
    return *this;
}

Stack<bool> &Stack<bool>::operator=(Stack<bool> &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

bool Stack<bool>::operator==(const Stack<bool> &other) const {
    if (size_ != other.size_) {
        return false;
    }

    for (uint16_t i = 0; i < size_ / BYTES_IN_CHAR; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }

    for (uint16_t i = 0; i < size_ % BYTES_IN_CHAR; ++i) {
        unsigned char elem1 = data_[(size_ - 1) / BYTES_IN_CHAR];
        elem1 = elem1 >> (i);
        elem1 &= 1U;

        unsigned char elem2 = other.data_[(size_ - 1) / BYTES_IN_CHAR];
        elem2 = elem2 >> (i);
        elem2 &= 1U;

        if (elem1 != elem2) {
            return false;
        }
    }
    return true;
}
