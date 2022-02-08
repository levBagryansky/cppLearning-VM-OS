#include <gtest/gtest.h>
#include "HashTable-impl.h"

const int BIG_NUM = 5e4;

TEST(HashTable, Length){
    HashTable ht1;
    for (int i = 0; i < 200; ++i) {
        ht1.Add("qwerty_" + std::to_string(i), i);
    }
    for (int i = 0; i < 200; ++i) {
        ht1.Add("hi" + std::to_string(i), i);
    }
    ASSERT_EQ(400, ht1.Length());

    HashTable ht2;
    for (int i = 0; i < BIG_NUM; ++i) {
        ht2.Add("qwerty_" + std::to_string(i), i);
        ht2.Add("hi" + std::to_string(i), i);
    }
    ASSERT_EQ(2 * BIG_NUM, ht2.Length());
}

TEST(HashTable, GetValue){
    HashTable ht;
    for (int i = 0; i < BIG_NUM; ++i) {
        ht.Add("qwerty_" + std::to_string(i), i);
        ht.Add("hi" + std::to_string(i), i);
    }

    for (int i = 0; i < BIG_NUM; ++i) {
        ASSERT_EQ(ht.GetValue("qwerty_" + std::to_string(i)), i);
    }

    ASSERT_NE(ht.GetValue("random string"), 5);
}

TEST(HashTable, HaveKey){
    HashTable ht;
    for (int i = 0; i < BIG_NUM; ++i) {
        ASSERT_NE(ht.HaveKey("qwerty_" + std::to_string(i)), true);
    }

    for (int i = 0; i < BIG_NUM; ++i) {
        ht.Add("qwerty_" + std::to_string(i), i);
        ht.Add("hi" + std::to_string(i), i);
    }

    for (int i = 0; i < BIG_NUM; ++i) {
        ASSERT_EQ(ht.HaveKey("qwerty_" + std::to_string(i)), true);
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}