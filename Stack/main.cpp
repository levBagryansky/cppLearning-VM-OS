#include <vector>
#include <algorithm>
#include "Stack.hpp"

int test();
int correctPushAndGetSize();
int correctPop();

int main() {
    test();
    return 0;
}

int test(){
    int errCode;
    int errSum = 0;

    if (errCode = correctPushAndGetSize()){
        std::cout << "Push or GetSize works incorrect: test " << errCode << std::endl;
        errSum++;
    }
    if (errCode = correctPop()){
        std::cout << "Pop works incorrect: test " << errCode << std::endl;
        errSum++;
    }

    if (!errSum){
        std::cout << "Nice!" << std::endl;
    }

    return errSum;
}

int correctPushAndGetSize(){
    Stack<int> s;
    for (int i = 0; i < 1000; ++i) {
        s.push(2*i + 89);
    }
    for (int i = 0; i < 10000; ++i) {
        s.push(-3 * i + 9999);
    }
    int len = s.getSize();
    if (len != 11000){
        return 1;
    }

    Stack<int> s2(s);
    for (int i = 0; i < 10000; ++i) {
        s2.push(-3 * i + 9999);
    }
    if (s2.getSize() != (len + 10000)){
        return 2;
    }


    return 0;
}

int correctPop(){
    Stack<int> s(20);
    for (int i = 0; i < 400; ++i) {
        s.push(i);
    }
    std::vector<int> vExample = {391, 392, 393, 394, 395, 396, 397, 398, 399};
    std::reverse(vExample.begin(), vExample.end());
    std::vector<int> v;
    for (int i = 0; i < 9; ++i) {
        int x = s.pop();
        v.push_back(x);
    }
    if (v != vExample && v.size() != 9){
        return 1;
    }

    Stack<double> s1(20);
    for (int i = 0; i < 400; ++i) {
        s1.push(i);
    }
    std::vector<double> vExampleDouble = {391, 392, 393, 394, 395, 396, 397, 398, 399};
    std::reverse(vExampleDouble.begin(), vExampleDouble.end());
    std::vector<double> v1;
    for (int i = 0; i < 9; ++i) {
        int x = s1.pop();
        v1.push_back(x);
    }
    if (v1 != vExampleDouble && v1.size() != 9){
        return 2;
    }
    return 0;
}