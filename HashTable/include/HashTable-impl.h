#ifndef HASHTABLE_IMPL_H
#define HASHTABLE_IMPL_H

#include <valarray>
#include <iostream>

const int const_val1 = 37;
const int const_val2 = 1;
const int start_capacity = 8;
int collusions = 0;

class HashTable{
public:
    HashTable();
    ~HashTable();
    void Add(const std::string& key, int value);
    size_t Length();
    bool HaveKey(const std::string& key);
    int GetValue(const std::string& key);
    void Print();

private:
    void Resize();
    size_t HashFunction(const std::string& key);

    struct Item{
        std::string key;
        int value;
        Item(): value(-1){};
    };

    size_t capacity_; // size of array
    size_t count_;    // count of items
    Item* data_;
};

HashTable::HashTable(): capacity_(start_capacity), count_(0), data_(new Item[start_capacity]) {}

HashTable::~HashTable() {
    delete[] data_;
}

size_t HashTable::HashFunction(const std::string &key) {
    size_t result = 0;
    for (int i = 0; i < key.length(); ++i) {
        result = (result + key[i] * static_cast<size_t>(pow(23, i))) % capacity_;
    }
    return result;
}

void HashTable::Add(const std::string &key, int value) {
    if (2 * count_ >= capacity_){
        Resize();
    }

    size_t index = HashFunction(key);
    int i = 0;
    while (data_[index].value != -1){
        //std::cout << "ALARM COLLUSION, INDEX = " << index << " HERE " << data_[index].key
        //<< " -> " << data_[index].value << ", NEW VALUE  = " << key <<  std::endl;
        collusions++;
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }

    data_[index].key = key;
    data_[index].value = value;
    count_++;
}

size_t HashTable::Length() {
    return count_;
}

void HashTable::Resize() {
    size_t prev_capacity = capacity_;
    capacity_ *= 2;
    Item* prev_data = data_;
    data_ = new Item[capacity_];
    count_ = 0;
    for (int i = 0; i < prev_capacity; ++i) {
        if (prev_data[i].value != -1){
            Add(prev_data[i].key, prev_data[i].value);
        }
    }
    delete[] prev_data;
}

bool HashTable::HaveKey(const std::string &key) {
    size_t index = HashFunction(key);
    int i = 0;
    while (data_[index].value != -1){
        if (data_[index].key == key){
            return true;
        }
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }

    return false;


}

int HashTable::GetValue(const std::string &key) {
    size_t index = HashFunction(key);
    int i = 0;
    while (data_[index].value != -1){
        if (data_[index].key == key){
            return data_[index].value;
        }
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }
    return -1;
}

void HashTable::Print() {
    for (int i = 0; i < capacity_; ++i) {
        if (data_[i].value != -1){
            std::cout << data_[i].key << " -> " << data_[i].value << std::endl;
        }
    }
    std::cout << "collusions = " << collusions << std::endl;
}

#endif //HASHTABLE_IMPL_H