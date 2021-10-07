#include "Stack.hpp"
#include <math.h>
#include <bitset>

template<class T>
Stack<T>::Stack(int len): size_(0), capacity_(len), data_(new T[len]){}

Stack<bool>::Stack(int len): size_(0), capacity_((len + 7)/8), data_(new char[capacity_]){}

template<class T>
Stack<T>::Stack(const Stack& other): size_(other.size_), capacity_(other.capacity_), data_(new T[other.capacity_]){
    std::copy(other.data_, other.data_ + size_, data_);
}

Stack<bool>::Stack(const Stack& other): size_(other.size_), capacity_(other.capacity_), data_(new char[(other.capacity_ + 7)/8]){
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
        char * newData = new char[2 * ((capacity_ + 7) / 8)];
        std::copy(data_, data_ + (size_ + 7) / 8, newData);
        delete[] data_;
        data_ = newData;
        capacity_ = 2 * ((capacity_ + 7) / 8) * 8;
    }

    data_[size_ / 8] += pow(2, size_ % 8);
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

template<class T>
T Stack<T>::top() const {
    if (size_ == 0){
        exit(2);
    }

    return data_[size_ - 1];
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T> &other) {
    if (this == &other){
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;

    data_ = new T[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
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

template<class T>
bool Stack<T>::operator==(const Stack<T> &other) {
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
        char hasElem = s.data_[i / 8];
        printf("Elem = %i\n", hasElem);
        //os << "Elem = " << hasElem << std::endl;
        hasElem  = hasElem >> (i % 8);
        //os << "Elem = " << std::bitset<32>(hasElem) << std::endl;
        hasElem &= 0b00000001;
        //os << hasElem << '(' << i << ") ";
    }

    return os;
}
