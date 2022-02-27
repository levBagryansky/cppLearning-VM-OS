#ifndef DICTIONARY_IMPL_H
#define DICTIONARY_IMPL_H

#include "HashTable-impl.h"
#include <fstream>

bool CorrectSymbol(char c);

std::string& FilterWord(std::string& word);

class Dictionary : public HashTable{
   public:
    Dictionary(int min_len, int max_len);
    void Update(const std::string& path);

   private:
    const int min_len_;
    const int max_len_;

    void AddKey(const std::string& key);
};

bool CorrectSymbol(char c){
    return (c >= 'a' && c <= 'z' || c == '-' || c == ' ');
}

std::string& FilterWord(std::string& word){ // filters to normal word
    for (int i = word.length() - 1; i >= 0; --i) {
        if (word[i] >= 'A' && word[i] <= 'Z'){
            word[i] += 'a' - 'A';
        }
    }

    int i = word.length() -1;
    while (i >= 0 && !CorrectSymbol(word[i])){
        word.erase(i, 1);
        i--;
    }

    i = 0;
    while (word.length() > 0 && !CorrectSymbol(word[i])){
        i++;
    }
    word.erase(0, i);

    for (int j = 0; j < word.length(); ++j) {
        if (!(word[j] >= 'a' && word[j] <= 'z' || word[j] == '-')){
            word = "";
            break;
        }
    }
    return word;
}

Dictionary::Dictionary(int min_len, int max_len): min_len_(min_len), max_len_(max_len){}

void Dictionary::Update(const std::string& path) {
    std::ifstream is{path};
    std::string next_word;
    while (is >> next_word){
        FilterWord(next_word);
        if (next_word.length() <= max_len_ && next_word.length() >= min_len_){
            AddKey(next_word);
        }
    }
}

void Dictionary::AddKey(const std::string& key){
    if (2 * count_ >= capacity_){
        Resize();
    }

    size_t index = HashFunction(key);
    int i = 0;

    //Looking for empty cell or cell with the same key
    while (data_[index].value != -1){
        if (data_[index].key == key){
            break;
        }
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }

    if (data_[index].value == -1){
        data_[index].key = key;
        data_[index].value = 1;
        count_++;
    } else{
        data_[index].value++;
    }
}

#endif //DICTIONARY_IMPL_H