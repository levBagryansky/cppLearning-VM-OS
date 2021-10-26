#include "Bool_Stack.h"
#include "Stack_impl.h"
#include <cmath>

Stack<bool>::Stack(): size_(0), capacity_((32 + 7)/8), data_(new unsigned char[capacity_]){}

Stack<bool>::Stack(size_t len): size_(0), capacity_((len + 7)/8), data_(new unsigned char[capacity_]){}

Stack<bool>::Stack(const Stack& other): size_(other.size_), capacity_(other.capacity_), data_(new unsigned char[(other.capacity_ + 7)/8]){
    std::copy(other.data_, other.data_ + (size_ + 7) / 8, data_);
}

Stack<bool>::Stack(Stack &&other): data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
}

Stack<bool>::~Stack(){
    delete[] data_;
}

int Stack<bool>::getSize() const {
    return size_;
}

bool Stack<bool>::isEmpty() const{
    return !size_;
}

void Stack<bool>::push(bool value) {
    if (size_ == capacity_){
        unsigned char * newData = new unsigned char[2 * ((capacity_ + 7) / 8)];
        std::copy(data_, data_ + (size_ + 7) / 8, newData);
        delete[] data_;
        data_ = newData;
        capacity_ = 2 * ((capacity_ + 7) / 8) * 8;
    }

    int i = size_ % 8;
    data_[size_ / 8] = ((data_[size_ / 8] & (~(1 << i))) + (value << i));
    size_++;
}

void Stack<bool>::pop(){
    if(size_ == 0){
        exit(1);
    }
    size_--;
}

bool Stack<bool>::top() const {
    if (size_ == 0){
        exit(2);
    }

    unsigned char containElem = data_[(size_-1)  / 8];
    containElem  = containElem >> ((size_-1) % 8);
    containElem &= 1;
    return containElem;
}

void Stack<bool>::swap(Stack<bool> &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

Stack<bool>& Stack<bool>::operator=(const Stack<bool> &other) {
    if (this == &other){
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;

    delete[] data_;
    data_ = new unsigned char [(capacity_ + 7) / 8];
    std::copy(other.data_, other.data_ + (size_ + 7) / 8 , data_);
    return *this;
}

Stack<bool>& Stack<bool>::operator=(Stack<bool>&& other) {
    if (this == &other){
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

bool Stack<bool>::operator==(const Stack<bool> &other) const{
    if (size_ != other.size_){
        return false;
    }

    for (int i = 0; i < size_ / 8; ++i) {
        if (data_[i] != other.data_[i]){
            return false;
        }
    }

    for (int i = 0; i < size_ % 8; ++i) {
        unsigned char elem1 = data_[(size_-1)  / 8];
        elem1  = elem1 >> (i);
        elem1 &= 1;

        unsigned char elem2 = other.data_[(size_-1)  / 8];
        elem2  = elem2 >> (i);
        elem2 &= 1;

        if (elem1 != elem2){
            return false;
        }
    }
    return true;
}

bool Stack<bool>::operator!=(const Stack<bool> &other) const{
    return !(operator==(other));
}
