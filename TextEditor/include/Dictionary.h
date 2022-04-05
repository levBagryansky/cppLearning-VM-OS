#ifndef DICTIONARY_IMPL_H
#define DICTIONARY_IMPL_H

#include "HashTable-impl.h"
#include <fstream>

bool CorrectSymbol(char c);
std::string *FilterWord(std::string *p_word);
int Levenshtein(const std::string& str1, const std::string& str2);

class Dictionary : public HashTable<std::string>{
   public:
    Dictionary(int min_len, int max_len);
    explicit Dictionary(int len = 0);
    void SetLen(uint len);
    void SetLen(uint min_len, uint max_len);
    void Update(const std::string& path);
    const std::string& BestWord(const std::string& word) const;
    void AddKey(const std::string& key);

   private:
    uint min_len_;
    uint max_len_;
};

#endif //DICTIONARY_IMPL_H