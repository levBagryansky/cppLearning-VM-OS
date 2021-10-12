#include "Stack.hpp"
#include "Stack-impl.h"
#include <cmath>

template<class T>
Stack<T>::Stack(int len): size_(0), capacity_(len), data_(new T[len]){}

Stack<bool>::Stack(int len): size_(0), capacity_((len + 7)/8), data_(new unsigned char[capacity_]){}

template<class T>
Stack<T>::Stack(const Stack& other): size_(other.size_), capacity_(other.capacity_), data_(new T[other.capacity_]){
    std::copy(other.data_, other.data_ + size_, data_);
}

Stack<bool>::Stack(const Stack& other): size_(other.size_), capacity_(other.capacity_), data_(new unsigned char[(other.capacity_ + 7)/8]){
    std::copy(other.data_, other.data_ + (size_ + 7) / 8, data_);
}

template<class T>
Stack<T>::Stack(Stack &&other): data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
}

Stack<bool>::Stack(Stack &&other): data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
}

template<class T>
Stack<T>::~Stack(){
    delete[] data_;
}

Stack<bool>::~Stack(){
    delete[] data_;
}

template<class T>
int Stack<T>::getSize() const {
    return size_;
}

int Stack<bool>::getSize() const {
    return size_;
}

template<class T>
bool Stack<T>::isEmpty() const{
    return !size_;
}

bool Stack<bool>::isEmpty() const{
    return !size_;
}

template<class T>
void Stack<T>::push(T value) {
    if (size_ == capacity_){
        T* newData = new T[2 * capacity_];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
        capacity_ *= 2;
    }

    data_[size_] = value;
    size_++;
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

template<class T>
T Stack<T>::pop(){
    if(size_ == 0){
        exit(1);
    }
    size_--;
    return data_[size_];
}

bool Stack<bool>::pop(){
    if(size_ == 0){
        exit(1);
    }
    size_--;
    unsigned char containElem = data_[size_ / 8];
    containElem  = containElem >> (size_ % 8);
    containElem &= 1;
    return containElem;
}

template<class T>
T Stack<T>::top() const {
    if (size_ == 0){
        exit(2);
    }

    return data_[size_ - 1];
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

template<class T>
void Stack<T>::swap(Stack<T> &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

void Stack<bool>::swap(Stack<bool> &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T> &other) {
    if (this == &other){
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
    delete[] data_;
    data_ = new T[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
    return *this;
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

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) {
    if (this == &other){
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
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

template<class T>
bool Stack<T>::operator==(const Stack<T> &other) const{
    if (size_ != other.size_){
        return false;
    }
    for (int i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]){
            return false;
        }
    }

    return true;
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

template<class T>
bool Stack<T>::operator!=(const Stack<T> &other) const{
    return !(operator==(other));
}

bool Stack<bool>::operator!=(const Stack<bool> &other) const{
    return !(operator==(other));
}

template<class T>
std::ostream& operator<<(std::ostream &os, Stack<T> &s){
    os << "This is Stack:" << " capacity_ = " << s.capacity_ << ", size_ = " << s.size_ << std::endl;
    for (int i = 0; i < s.size_; ++i) {
        os << s.data_[i] << '(' << i << ") ";

    }

    return os;
}

std::ostream& operator<<(std::ostream &os, Stack<bool> &s){
    os << "This is Stack:" << " capacity_ = " << s.capacity_ << ", size_ = " << s.size_ << std::endl;
    for (int i = 0; i < s.size_; ++i) {
        unsigned char containElem = s.data_[i / 8];
        containElem  = containElem >> (i % 8);
        containElem &= 1;
        containElem += '0';
        os << containElem << '(' << i << ") ";
    }

    return os;
}

