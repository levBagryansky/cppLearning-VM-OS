#include "Stack.hpp"

Stack::Stack(int len): size_(0), capacity_(32), data_(new int(len)){}

Stack::Stack(const Stack& other){

}

Stack::~Stack(){
    delete[] data_;
}

