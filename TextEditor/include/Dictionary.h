#ifndef DICTIONARY_IMPL_H
#define DICTIONARY_IMPL_H

#include "HashTable.h"
#include <fstream>

bool CorrectSymbol(char c);
std::string *FilterWord(std::string *p_word);
int Levenshtein(const std::string& str1, const std::string& str2);

class Dictionary : public HashTable{
   public:
    Dictionary(int min_len, int max_len);
    explicit Dictionary(int len = 0);
    ~Dictionary();
    void SetLen(int len);
    void SetLen(int min_len, int max_len);
    void AddKey(const std::string& key);
    void Update(const std::string& path);
    const std::string& BestWord(const std::string& word);

   private:
    uint min_len_;
    uint max_len_;
    std::mutex* mutexes_;
};

#endif //DICTIONARY_IMPL_H