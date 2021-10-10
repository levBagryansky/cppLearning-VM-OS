#include <vector>
#include <algorithm>
#include "Stack.hpp"

int test();
int correctPushAndGetSize();
int correctPop();
int correctTop();
int correctIsEmpty();
int correctEqual();
int correctSwap();

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

    if (errCode = correctTop()){
        std::cout << "Top works incorrect: test " << errCode << std::endl;
        errSum++;
    }

    if (errCode = correctIsEmpty()){
        std::cout << "IsEmpty works incorrect:  test " << errCode << std::endl;
        errSum++;
    }

    if (errCode = correctEqual()){
        std::cout << "Operator == works incorrect:  test " << errCode << std::endl;
        errSum++;
    }

    if (errCode = correctSwap()){
        std::cout << "Swap works incorrect:  test " << errCode << std::endl;
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

    Stack<bool> bools;
    for (int i = 0; i < 10000; ++i) {
        bools.push(i % 2);
    }
    int size = bools.getSize();
    if (size != 10000){
        return 3;
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

    std::vector<bool> vExampleBools = {1, 1, 0, 1, 1, 0, 0, 0, 1};
    Stack<bool> sBools;
    for (int i = vExampleBools.size() - 1; i >= 0; --i) {
        sBools.push(vExampleBools[i]);
    }
    std::vector<bool> vBools;
    int sBoolsLen = sBools.getSize();
    for (int i = 0; i < sBoolsLen; ++i) {
        vBools.push_back(sBools.pop());
    }
    if(vExampleBools != vBools){
        return 3;
    }

    if(sBools.getSize() != 0){
        return 4;
    }

    std::vector<bool> v1Bools;
    std::vector<bool> v1ExampleBools = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 , 0, 1, 1, 0, 1, 1, 0, 0};
    Stack<bool> s1Bools;
    for (int i = v1ExampleBools.size() - 1; i >= 0; --i) {
        s1Bools.push(v1ExampleBools[i]);
    }
    int s1BoolsLen = v1ExampleBools.size();
    for (int i = 0; i < s1BoolsLen; ++i) {
        bool b = s1Bools.pop();
        //std::cout << b << ' ';
        v1Bools.push_back(b);
    }
    if(v1ExampleBools != v1Bools){
        std::cout << "Incorrect" << std::endl;
        return 5;
    }

    if(s1Bools.getSize() != 0){
        return 6;
    }

    return 0;
}

int correctTop(){
    Stack<int> s;
    for (int i = 0; i < 999; ++i) {
        s.push(i * 2);
    }
    int lastNum = s.top();
    if (lastNum != (2 * 998)){
        return 1;
    }

    s.push(-99909);
    if (s.top() != -99909){
        return 2;
    }

    Stack<double> doubles;
    for (int i = 0; i < 432; ++i) {
        doubles.push(i / 2);
    }
    double lastDouble = doubles.top();
    if (abs(lastDouble - 431/2) > 1e-8){
        return 3;
    }

    Stack<bool> sBools;
    std::vector<bool> vBools = {1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0};
    for (bool item: vBools){
        sBools.push(item);
    }
    if (sBools.top() != 0){
        return 4;
    }

    sBools.pop();
    if (sBools.top() != 1){
        return 5;
    }

    sBools.pop();
    if (sBools.top() != 0){
        return 6;
    }

    return 0;
}

int correctIsEmpty(){
    Stack<double>  doubles{5};
   if(!doubles.isEmpty()){
       return 1;;
   }

    doubles.push(4);
    if (doubles.isEmpty()){
        return 2;
    }

    doubles.pop();
    if (!doubles.isEmpty())
    {
        return 3;
    }

    Stack<bool> bools;
    if (!(bools.isEmpty())){
        return 4;
    }

    return 0;
}

int correctEqual(){
    Stack<int> ints1;
    Stack<int> ints2;
    if (!(ints1 == ints2)){
        return 1;
    }

    Stack<double> doubles1;
    Stack<double> doubles2;
    if (!(doubles1 == doubles2)){
        return 2;
    }

    for (int i = 0; i < 900; ++i) {
        ints1.push(i);
    }
    for (int i = 0; i < 100; ++i) {
        ints1.pop();
    }
    for (int i = 0; i < 800; ++i) {
        ints2.push(i);
    }

    if (!(ints1 == ints2)){
        return 3;
    }

    ints1.push(9);
    if (ints1 == ints2){
        return 4;
    }

    Stack<bool> bools1, bools2;
    std::vector<bool> vBools = {1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0};
    for (bool item: vBools){
        bools1.push(item);
        bools2.push(item);
    }
    if (!(bools1 == bools2)){
        return 5;
    }

    bools1.pop();
    if (bools1 == bools2){
        return 6;
    }
    return 0;
}

int correctSwap(){
    Stack<int> ints1, ints2, ints1Buf, ints2Buf;
    ints1.push(1);
    ints1.push(2);
    ints1.push(3);
    ints2.push(9);
    ints1Buf = ints1;
    ints2Buf = ints2;
    ints1.swap(ints2);
    if (!(ints1 == ints2Buf && ints2 == ints1Buf)){
        return 1;
    }

    for (int i = 0; i < 1e4; ++i) {
        ints1.push(i);
        ints2.push(10 * i);
    }
    ints1Buf = ints1;
    ints2Buf = ints2;
    ints1.swap(ints2);
    if (!(ints1 == ints2Buf && ints2 == ints1Buf)){
        return 2;
    }

    if (ints1 == ints2){
        return 3;
    }

    Stack<bool> bools1, bools2, bools1Buf, bools2Buf;
    for (int i = 0; i < 200; ++i) {
        bools1.push(0);
        bools2.push(1);
    }
    bools1Buf = bools1;
    bools2Buf = bools2;
    bools1.swap(bools2);
    if (!((bools2 == bools1Buf) && (bools1 == bools2Buf))){
        return 4;
    }

    if (bools1 == bools2){
        return 5;
    }

    return 0;
}
