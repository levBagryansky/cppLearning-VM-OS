#include "Stack.hpp"

template<typename T>
Stack<T>::Stack(int len): size_(0), capacity_(32), data_(new T(len)){}

template<typename T>
Stack<T>::Stack(const Stack& other): size_(other.size_), capacity_(other.capacity_), data_(new int[capacity_]){
    std::copy(other.data_, other.data_ + size_, data_);
}

template<typename T>
Stack<T>::Stack(Stack &&other): data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
}

template<typename T>
Stack<T>::~Stack(){
    delete[] data_;
}

template<typename T>
void Stack<T>::push(int x) {
    if (size_ == capacity_){

    }
}
