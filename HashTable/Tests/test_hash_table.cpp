#include <gtest/gtest.h>
#include "TextEditor-impl.h"

const int BIG_NUM = 1e6;
const std::string path = "../../Tests/lord_of_rings.txt";

TEST(HashTable, Length){
    HashTable ht1;
    for (int i = 0; i < 200; ++i) {
        ht1.AddPair("qwerty_" + std::to_string(i), i);
    }
    for (int i = 0; i < 200; ++i) {
        ht1.AddPair("hi" + std::to_string(i), i);
    }
    ASSERT_EQ(400, ht1.Length());

    HashTable ht2;
    for (int i = 0; i < BIG_NUM; ++i) {
        ht2.AddPair("qwerty_" + std::to_string(i), i);
        ht2.AddPair("hi" + std::to_string(i), i);
    }
    ASSERT_EQ(2 * BIG_NUM, ht2.Length());
}

TEST(HashTable, GetValue){
    HashTable ht;
    for (int i = 0; i < BIG_NUM; ++i) {
        ht.AddPair("qwerty_" + std::to_string(i), i);
        ht.AddPair("hi" + std::to_string(i), i);
    }

    for (int i = 0; i < BIG_NUM; ++i) {
        ASSERT_EQ(ht.GetValue("qwerty_" + std::to_string(i)), i);
    }

    ASSERT_NE(ht.GetValue("random string"), 5);
}

TEST(HashTable, CopyConstuctor){
    HashTable ht;
    for (int i = 0; i < BIG_NUM; ++i) {
        ht.AddPair("qwerty_" + std::to_string(i), i);
        ht.AddPair("hi" + std::to_string(i), i);
    }

    HashTable copied_ht(ht);

    for (int i = 0; i < BIG_NUM; ++i) {
        ASSERT_EQ(copied_ht.GetValue("qwerty_" + std::to_string(i)), i);
    }

    ASSERT_NE(copied_ht.GetValue("random string"), 5);
}

TEST(HashTable, MoveConstuctor){
    HashTable ht;
    for (int i = 0; i < BIG_NUM; ++i) {
        ht.AddPair("qwerty_" + std::to_string(i), i);
        ht.AddPair("hi" + std::to_string(i), i);
    }

    HashTable moved_ht(std::move(ht));

    for (int i = 0; i < BIG_NUM; ++i) {
        ASSERT_EQ(moved_ht.GetValue("qwerty_" + std::to_string(i)), i);
    }

    ASSERT_NE(moved_ht.GetValue("random string"), 5);
}

TEST(HashTable, HaveKey){
    HashTable ht;
    for (int i = 0; i < BIG_NUM; ++i) {
        ASSERT_NE(ht.HaveKey("qwerty_" + std::to_string(i)), true);
    }

    for (int i = 0; i < BIG_NUM; ++i) {
        ht.AddPair("qwerty_" + std::to_string(i), i);
        ht.AddPair("hi" + std::to_string(i), i);
    }

    for (int i = 0; i < BIG_NUM; ++i) {
        ASSERT_EQ(ht.HaveKey("qwerty_" + std::to_string(i)), true);
    }
}

TEST(syntax_functions, FilterWord){
    std::string word = "[]Hi,,,{}";
    ASSERT_EQ("hi", FilterWord(word));

    word = "[]H;i,,,{}";
    ASSERT_EQ("", FilterWord(word));
}

TEST(syntax_functions, Levenshtein){
    ASSERT_EQ(Levenshtein("qwerty", "qwdfgt"), 4);
    ASSERT_EQ(Levenshtein("cnhjrf", "cj,frf"), 3);
    ASSERT_EQ(Levenshtein("qwerty", "qwerty"), 0);
    ASSERT_EQ(Levenshtein("doctor", "dogtor"), 1);
}

TEST(Dictionary, Update){
    Dictionary dk(2, 8);
    dk.Update(path);

    std::map<std::string, int> m;
    std::ifstream is{path};
    std::string next_word;
    while (is >> next_word){
        FilterWord(next_word);
        if (next_word.length() <= 8 && next_word.length() >= 2){
            m[next_word]++;
        }
    }
    std::cout << std::endl;

    for (const auto& pair: m) {
        ASSERT_EQ(pair.second, dk.GetValue(pair.first));
    }
}

TEST(TextEditor, HaveWord){
    TextEditor te;
    te.Upload(path);

    std::ifstream is{path};
    ASSERT_TRUE(is.is_open());
    std::string next_word;
    while (is >> next_word){
        FilterWord(next_word);
        if (next_word.length() <= MAX_WORD_LEN && next_word.length() >= 2){
            ASSERT_TRUE(te.HaveWord(next_word));
        } else{
            ASSERT_FALSE(te.HaveWord(next_word));
        }
    }

    ASSERT_FALSE(te.HaveWord("1234567890123456789012345"));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}