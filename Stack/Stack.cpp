#include "Stack.hpp"

Stack::Stack(int len): size_(0), capacity_(32), data_(new int(len)){}

Stack::Stack(const Stack& other): size_(other.size_), capacity_(other.capacity_), data_(new int[capacity_]){
    std::copy(other.data_, other.data_ + size_, data_);
}

Stack::Stack(Stack &&other): data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
}

Stack::~Stack(){
    delete[] data_;
}

void Stack::push(int x) {
    if (size_ == capacity_){

    }


}
