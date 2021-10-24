#ifndef STACK_IMPL_H
#define STACK_IMPL_H
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
    void push(T value);
    void pop();
    T& top() const;
    void swap(Stack<T> &other);

    void pushWithFactor(T x, long double factor);

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
bool Stack<T>::isEmpty() const{
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

template<class T>
void Stack<T>::pop(){
    if(size_ == 0){
        exit(1);
    }
    size_--;
}

template<class T>
T& Stack<T>::top() const {
    if (size_ == 0){
        exit(2);
    }

    return data_[size_ - 1];
}

template<class T>
void Stack<T>::swap(Stack<T> &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

template<class T>
void Stack<T>::pushWithFactor(T value, long double factor){
    if (size_ == capacity_){
        T* newData = new T[factor * capacity_];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
        capacity_ *= factor;
    }

    data_[size_] = value;
    size_++;
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


template<class T>
bool Stack<T>::operator!=(const Stack<T> &other) const{
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

#endif //STACK_IMPL_H