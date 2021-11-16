#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include "Stack.h"

#include <iostream>

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
        bools.push(static_cast<bool> (i % 2));
    }
    int size = bools.getSize();
    ASSERT_EQ(size, 10000);
}

TEST(POP, POP) {
    Stack<int> s(20);
    for (int i = 0; i < 400; ++i) {
        s.push(i);
    }
    std::vector<int> v_example = {391, 392, 393, 394, 395, 396, 397, 398, 399};
    std::reverse(v_example.begin(), v_example.end());
    std::vector<int> v;
    for (int i = 0; i < 9; ++i) {
        int x = s.top();
        s.pop();
        v.push_back(x);
    }
    ASSERT_EQ(v, v_example);
    ASSERT_EQ(v.size(), 9);

    Stack<double> s1(20);
    for (int i = 0; i < 400; ++i) {
        s1.push(i);
    }
    std::vector<double> v_example_double = {391, 392, 393, 394, 395,
                                          396, 397, 398, 399};
    std::reverse(v_example_double.begin(), v_example_double.end());
    std::vector<double> v1;
    for (int i = 0; static_cast<std::vector<double>::size_type>(i) < v_example_double.size(); ++i) {
        int x = s1.top();
        v1.push_back(x);
        s1.pop();
    }
    ASSERT_EQ(v1, v_example_double);

    std::vector<bool> v_example_bools = {true,  false, false, true, true,
                                       false, false, false, true};
    Stack<bool> s_bools;
    for (int i = static_cast<int>(v_example_bools.size()) - 1; i >= 0; --i) {
        s_bools.push(v_example_bools[i]);
    }
    std::vector<bool> v_bools;
    int s_bools_len = s_bools.getSize();
    for (int i = 0; i < s_bools_len; ++i) {
        v_bools.push_back(s_bools.top());
        s_bools.pop();
    }
    ASSERT_EQ(v_example_bools, v_bools);
    ASSERT_EQ(s_bools.getSize(), 0);

    std::vector<bool> v1_bools;
    std::vector<bool> v1_example_bools = {
        true,  false, true, true, true, true, false, true, true, true, false,
        true,  false, true, true, true, true, true,  true, true, true, true,
        false, true,  true, true, true, true, false, true, false};
    Stack<bool> s1_bools;
    for (int i = static_cast<int>(v1_example_bools.size()) - 1; i >= 0; --i) {
        s1_bools.push(v1_example_bools[i]);
    }
    int s1_bools_len = v1_example_bools.size();
    for (int i = 0; i < s1_bools_len; ++i) {
        bool b = s1_bools.top();
        s1_bools.pop();
        v1_bools.push_back(b);
    }
    ASSERT_EQ(v1_example_bools, v1_bools);
    ASSERT_EQ(s1_bools.getSize(), 0);
}

TEST(TOP, TOP) {
    Stack<int> s;
    for (int i = 0; i < 999; ++i) {
        s.push(i * 2);
    }
    int last_num = s.top();
    ASSERT_EQ(last_num, 2 * 998);

    s.push(-99909);
    ASSERT_EQ(s.top(), -99909);

    Stack<double> doubles;
    for (int i = 0; i < 432; ++i) {
        doubles.push(static_cast<double>(i) / 2);
    }
    double last_double = doubles.top();
    ASSERT_DOUBLE_EQ(last_double, static_cast<double>(431) / 2);

    Stack<bool> s_bools;
    std::vector<bool> v_bools(1000);
    for (int i = 0; i < 1000; ++i) {
        v_bools.push_back(static_cast<bool>(rand() % 2 == 1));
    }
    for (bool item : v_bools) {
        s_bools.push(item);
    }
    ASSERT_EQ(s_bools.top(), v_bools[v_bools.size() - 1]);

    s_bools.pop();
    ASSERT_EQ(s_bools.top(), v_bools[v_bools.size() - 2]);

    s_bools.pop();
    ASSERT_EQ(s_bools.top(), v_bools[v_bools.size() - 3]);
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

    Stack<bool> bools1;
    Stack<bool> bools2;
    std::vector<bool> v_bools(100000);
    for (int i = 0; i < 100000; ++i) {
        v_bools.push_back(static_cast<bool>(rand() % 2 == 1));
    }
    for (bool item : v_bools) {
        bools1.push(item);
        bools2.push(item);
    }
    ASSERT_TRUE(bools1 == bools2);

    bools1.pop();
    ASSERT_FALSE(bools1 == bools2);
}

TEST(SWAP, SWAP) {
    Stack<int> ints1;
    Stack<int> ints2;
    Stack<int> ints1_buf;
    Stack<int> ints2_buf;
    ints1.push(1);
    ints1.push(2);
    ints1.push(3);
    ints2.push(9);
    ints1_buf = ints1;
    ints2_buf = ints2;
    ints1.swap(ints2);
    ASSERT_TRUE(ints1 == ints2_buf);
    ASSERT_TRUE(ints2 == ints1_buf);

    for (int i = 0; i < 1e4; ++i) {
        ints1.push(i);
        ints2.push(10 * i);
    }
    ints1_buf = ints1;
    ints2_buf = ints2;
    ints1.swap(ints2);
    ASSERT_TRUE(ints1 == ints2_buf);
    ASSERT_TRUE(ints2 == ints1_buf);
    ASSERT_FALSE(ints1 == ints2);

    Stack<bool> bools1;
    Stack<bool> bools2;
    Stack<bool> bools1_buf;
    Stack<bool> bools2_buf;
    for (int i = 0; i < 200; ++i) {
        bools1.push(false);
        bools2.push(true);
    }
    bools1_buf = bools1;
    bools2_buf = bools2;
    bools1.swap(bools2);
    ASSERT_TRUE(bools2 == bools1_buf);
    ASSERT_TRUE(bools1 == bools2_buf);
    ASSERT_FALSE(bools1 == bools2);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}