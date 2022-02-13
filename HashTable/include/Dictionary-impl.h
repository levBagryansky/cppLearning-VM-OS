#ifndef DICTIONARY_IMPL_H
#define DICTIONARY_IMPL_H

#include "HashTable-impl.h"

class Dictionary : public HashTable{
    void AddKey(const std::string& key);
};

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
    } else{
        data_[index].value++;
    }
}

#endif //DICTIONARY_IMPL_H
