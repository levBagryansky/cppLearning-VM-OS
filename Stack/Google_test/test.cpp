#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "Stack.h"

TEST(PushAndGetSize, PushAndGetSize) {
    Stack<int> s;
    for (int i = 0; i < 1000; ++i) {
        s.push(2 * i + 89);
    }
    for (int i = 0; i < 10000; ++i) {
        s.push(-3 * i + 9999);
    }
    int len = s.getSize();
    ASSERT_EQ(len, 11000);

    Stack<int> s2(s);
    for (int i = 0; i < 10000; ++i) {
        s2.push(-3 * i + 9999);
    }
    ASSERT_EQ(s2.getSize(), len + 10000);

    Stack<bool> bools;
    for (int i = 0; i < 10000; ++i) {
        bools.push(i % 2);
    }
    int size = bools.getSize();
    ASSERT_EQ(size, 10000);
}

TEST(POP, POP) {
    Stack<int> s(20);
    for (int i = 0; i < 400; ++i) {
        s.push(i);
    }
    std::vector<int> vExample = {391, 392, 393, 394, 395, 396, 397, 398, 399};
    std::reverse(vExample.begin(), vExample.end());
    std::vector<int> v;
    for (int i = 0; i < 9; ++i) {
        int x = s.top();
        s.pop();
        v.push_back(x);
    }
    ASSERT_EQ(v, vExample);
    ASSERT_EQ(v.size(), 9);

    Stack<double> s1(20);
    for (int i = 0; i < 400; ++i) {
        s1.push(i);
    }
    std::vector<double> vExampleDouble = {391, 392, 393, 394, 395,
                                          396, 397, 398, 399};
    std::reverse(vExampleDouble.begin(), vExampleDouble.end());
    std::vector<double> v1;
    for (int i = 0; static_cast<std::vector<double>::size_type>(i) < vExampleDouble.size(); ++i) {
        int x = s1.top();
        v1.push_back(x);
        s1.pop();
    }
    ASSERT_EQ(v1, vExampleDouble);

    std::vector<bool> vExampleBools = {true,  false, false, true, true,
                                       false, false, false, true};
    Stack<bool> sBools;
    for (int i = vExampleBools.size() - 1; i >= 0; --i) {
        sBools.push(vExampleBools[i]);
    }
    std::vector<bool> vBools;
    int sBoolsLen = sBools.getSize();
    for (int i = 0; i < sBoolsLen; ++i) {
        vBools.push_back(sBools.top());
        sBools.pop();
    }
    ASSERT_EQ(vExampleBools, vBools);
    ASSERT_EQ(sBools.getSize(), 0);

    std::vector<bool> v1Bools;
    std::vector<bool> v1ExampleBools = {
        true,  false, true, true, true, true, false, true, true, true, false,
        true,  false, true, true, true, true, true,  true, true, true, true,
        false, true,  true, true, true, true, false, true, false};
    Stack<bool> s1Bools;
    for (int i = v1ExampleBools.size() - 1; i >= 0; --i) {
        s1Bools.push(v1ExampleBools[i]);
    }
    int s1BoolsLen = v1ExampleBools.size();
    for (int i = 0; i < s1BoolsLen; ++i) {
        bool b = s1Bools.top();
        s1Bools.pop();
        // std::cout << b << ' ';
        v1Bools.push_back(b);
    }
    ASSERT_EQ(v1ExampleBools, v1Bools);
    ASSERT_EQ(s1Bools.getSize(), 0);
}

TEST(TOP, TOP) {
    Stack<int> s;
    for (int i = 0; i < 999; ++i) {
        s.push(i * 2);
    }
    int lastNum = s.top();
    ASSERT_EQ(lastNum, 2 * 998);

    s.push(-99909);
    ASSERT_EQ(s.top(), -99909);

    Stack<double> doubles;
    for (int i = 0; i < 432; ++i) {
        doubles.push(i / 2);
    }
    double lastDouble = doubles.top();
    ASSERT_DOUBLE_EQ(lastDouble, 431 / 2);
    /*if (abs(lastDouble - 431/2) > 1e-8){
        return 3;
    }*/

    Stack<bool> sBools;
    std::vector<bool> vBools;
    for (int i = 0; i < 1000; ++i) {
        vBools.push_back(rand() % 2 == 1);
    }
    for (bool item : vBools) {
        sBools.push(item);
    }
    ASSERT_EQ(sBools.top(), vBools[vBools.size() - 1]);

    sBools.pop();
    ASSERT_EQ(sBools.top(), vBools[vBools.size() - 2]);

    sBools.pop();
    ASSERT_EQ(sBools.top(), vBools[vBools.size() - 3]);
}

TEST(IsEmpty, IsEmpty) {
    Stack<double> doubles{5};
    ASSERT_TRUE(doubles.isEmpty());

    doubles.push(4);
    ASSERT_FALSE(doubles.isEmpty());

    doubles.pop();
    ASSERT_TRUE(doubles.isEmpty());

    Stack<bool> bools;
    ASSERT_TRUE(bools.isEmpty());
}

TEST(EQUAL, EQUAL) {
    Stack<int> ints1;
    Stack<int> ints2;
    ASSERT_TRUE(ints1 == ints2);

    Stack<double> doubles1;
    Stack<double> doubles2;
    ASSERT_TRUE(doubles1 == doubles2);

    for (int i = 0; i < 900; ++i) {
        ints1.push(i);
    }
    for (int i = 0; i < 100; ++i) {
        ints1.pop();
    }
    for (int i = 0; i < 800; ++i) {
        ints2.push(i);
    }
    ASSERT_TRUE(ints1 == ints2);

    ints1.push(9);
    ASSERT_FALSE(ints1 == ints2);

    Stack<bool> bools1, bools2;
    std::vector<bool> vBools;
    for (int i = 0; i < 100000; ++i) {
        vBools.push_back(rand() % 2 == 1);
    }
    for (bool item : vBools) {
        bools1.push(item);
        bools2.push(item);
    }
    ASSERT_TRUE(bools1 == bools2);

    bools1.pop();
    ASSERT_FALSE(bools1 == bools2);
}

TEST(SWAP, SWAP) {
    Stack<int> ints1, ints2, ints1Buf, ints2Buf;
    ints1.push(1);
    ints1.push(2);
    ints1.push(3);
    ints2.push(9);
    ints1Buf = ints1;
    ints2Buf = ints2;
    ints1.swap(ints2);
    ASSERT_TRUE(ints1 == ints2Buf);
    ASSERT_TRUE(ints2 == ints1Buf);

    for (int i = 0; i < 1e4; ++i) {
        ints1.push(i);
        ints2.push(10 * i);
    }
    ints1Buf = ints1;
    ints2Buf = ints2;
    ints1.swap(ints2);
    ASSERT_TRUE(ints1 == ints2Buf);
    ASSERT_TRUE(ints2 == ints1Buf);
    ASSERT_FALSE(ints1 == ints2);

    Stack<bool> bools1, bools2, bools1Buf, bools2Buf;
    for (int i = 0; i < 200; ++i) {
        bools1.push(0);
        bools2.push(1);
    }
    bools1Buf = bools1;
    bools2Buf = bools2;
    bools1.swap(bools2);
    ASSERT_TRUE(bools2 == bools1Buf);
    ASSERT_TRUE(bools1 == bools2Buf);
    ASSERT_FALSE(bools1 == bools2);
}

TEST(EXIT, INT_POP) {
    Stack<int> ints1;
    for (int i = 0; i < 100000; ++i) {
        ints1.push(i);
    }
    for (int i = 0; i < 100000; ++i) {
        ints1.pop();
    }
    ints1.pop();
    FAIL();
}

TEST(EXIT, INT_TOP) {
    Stack<int> ints;
    for (int i = 0; i < 100000; ++i) {
        ints.push(i);
    }
    for (int i = 0; i < 100000; ++i) {
        ints.pop();
    }
    ints.top();
    FAIL();
}

TEST(EXIT, BOOL_POP) {
    Stack<bool> bools;
    for (int i = 0; i < 100000; ++i) {
        bools.push(true);
    }
    for (int i = 0; i < 100000; ++i) {
        bools.pop();
    }
    bools.pop();
    FAIL();
}

TEST(EXIT, BOOL_TOP) {
    Stack<bool> bools;
    for (int i = 0; i < 100000; ++i) {
        bools.push(true);
    }
    for (int i = 0; i < 100000; ++i) {
        bools.pop();
    }
    bools.top();
    FAIL();
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}