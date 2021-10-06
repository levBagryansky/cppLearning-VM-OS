#include "Stack.hpp"

template<class T>
Stack<T>::Stack(int len): size_(0), capacity_(len), data_(new T[len]){}

template<class T>
Stack<T>::Stack(const Stack& other): size_(other.size_), capacity_(other.capacity_), data_(new T[other.capacity_]){
    std::copy(other.data_, other.data_ + size_, data_);
}

template<class T>
Stack<T>::Stack(Stack &&other): data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
}

template<class T>
Stack<T>::~Stack(){
    delete[] data_;
}

template<class T>
int Stack<T>::getSize() const {
    return size_;
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

template<class T>
T Stack<T>::pop() {
    size_--;
    return data_[size_];
}

template<class T>
std::ostream& operator<<(std::ostream &os, Stack<T> &s){
    os << "This is Stack:" << " capacity_ = " << s.capacity_ << ", size_ = " << s.size_ << std::endl;
    for (int i = 0; i < s.size_; ++i) {
        os << s.data_[i] << '(' << i << ") ";
    }

    return os;
}

template <class T>
T minimum(const T& lhs, const T& rhs)
{
    return lhs < rhs ? lhs : rhs;
}