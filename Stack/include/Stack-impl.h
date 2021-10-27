#ifndef STACK_IMPL_H
#define STACK_IMPL_H
#include <iostream>

template<class T>
class BoolStack {
public:
    BoolStack();
    BoolStack(size_t len);
    BoolStack(const BoolStack &other);
    BoolStack(BoolStack &&other);
    ~BoolStack();

    int getSize() const;
    bool isEmpty() const;
    void push(T value);
    void pop();
    T& top() const;
    void swap(BoolStack<T> &other);

    void changeFactor(double newFactor);

    BoolStack& operator=(const BoolStack &other);
    BoolStack& operator=(BoolStack &&other);
    bool operator== (const BoolStack<T>& other) const;
    bool operator!= (const BoolStack<T>& other) const;

private:
    double factor;
    size_t size_;
    size_t capacity_;
    T *data_;
};

template<class T>
BoolStack<T>::BoolStack(): factor(1.65), size_(0), capacity_(32), data_(new T[32]){}

template<class T>
BoolStack<T>::BoolStack(size_t len): factor(1.75), size_(0), capacity_(len), data_(new T[len]){}

template<class T>
BoolStack<T>::BoolStack(const BoolStack& other): factor(other.factor), size_(other.size_), capacity_(other.capacity_), data_(new T[other.capacity_]){
    std::copy(other.data_, other.data_ + size_, data_);
}

template<class T>
BoolStack<T>::BoolStack(BoolStack &&other): factor(other.factor), data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
}

template<class T>
BoolStack<T>::~BoolStack(){
    delete[] data_;
}

template<class T>
int BoolStack<T>::getSize() const {
    return size_;
}

template<class T>
bool BoolStack<T>::isEmpty() const{
    return !size_;
}

template<class T>
void BoolStack<T>::push(T value) {
    if (size_ == capacity_){
        T* newData = new T[static_cast<int>(factor * capacity_)];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
        capacity_ = static_cast<int>(factor * capacity_);
    }

    data_[size_] = value;
    size_++;
}

template<class T>
void BoolStack<T>::pop(){
    if(size_ == 0){
        exit(1);
    }
    size_--;
}

template<class T>
T& BoolStack<T>::top() const {
    if (size_ == 0){
        exit(2);
    }

    return data_[size_ - 1];
}

template<class T>
void BoolStack<T>::swap(BoolStack<T> &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

template<class T>
void BoolStack<T>::changeFactor(double newFactor){
    if (newFactor > 1) {
        factor = newFactor;
    }
    else{
        exit(1);
    }
}

template<class T>
BoolStack<T>& BoolStack<T>::operator=(const BoolStack<T> &other) {
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

template<class T>
BoolStack<T>& BoolStack<T>::operator=(BoolStack<T>&& other) {
    if (this == &other){
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
}

template<class T>
bool BoolStack<T>::operator==(const BoolStack<T> &other) const{
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
bool BoolStack<T>::operator!=(const BoolStack<T> &other) const{
    return !(operator==(other));
}

#endif //STACK_IMPL_H