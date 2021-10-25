#include <iostream>
#include "Stack_impl.h"

int main(){
    Stack<int>* ps = new Stack<int>;
    for (int i = 0; i < 100000; ++i) {
        (*ps).pushWithFactor(i, 1.6);
        std::cout << ".";
    }
    delete ps;
    std::cout << std::endl <<  "Hello world!" << std::endl;

}