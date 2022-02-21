#ifndef HASHTABLE_IMPL_H
#define HASHTABLE_IMPL_H

#include <valarray>
#include <iostream>

const int const_val1 = 37;
const int const_val2 = 1;
const int hash_val = 23;
const int start_capacity = 60e3;

class HashTable{
public:
    HashTable();
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    ~HashTable();
    void AddPair(const std::string& key, int value);
    size_t Length();
    bool HaveKey(const std::string& key);
    int GetValue(const std::string& key);
    int GetCollisions();
    void Print();

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other);

protected:
    void Resize();
    size_t HashFunction(const std::string& key);
    size_t GetIndex(const std::string& key);

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

HashTable::HashTable(const HashTable& other): capacity_(other.capacity_), count_(other.count_), data_(new Item[other.capacity_]){
    std::copy(other.data_, other.data_ + capacity_, data_);
}

HashTable::HashTable(HashTable&& other) noexcept: capacity_(other.capacity_), count_(other.count_), data_(other.data_){
    other.data_ = nullptr;
}

HashTable::~HashTable() {
    delete[] data_;
}

size_t HashTable::HashFunction(const std::string &key) {
    size_t result = 0;
    for (int i = 0; i < key.length(); ++i) {
        result = (result + key[i] * static_cast<size_t>(pow(hash_val, i))) % capacity_;
    }
    return result;
}

size_t HashTable::GetIndex(const std::string& key) {
    size_t index = HashFunction(key);
    int i = 0;
    while (data_[index].value != -1){
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }

    return index;
}

void HashTable::AddPair(const std::string &key, int value) {
    if (2 * count_ >= capacity_){
        Resize();
    }

    size_t index = GetIndex(key);

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
            AddPair(prev_data[i].key, prev_data[i].value);
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

int HashTable::GetCollisions() {
    int result = 0;
    for (int i = 0; i < capacity_; ++i) {
        if ((data_[i].value != -1) && (i != HashFunction(data_[i].key))){
            result++;
        }
    }

    return result;
}

void HashTable::Print() {
    int figure_of_words = 0;

    for (int i = 0; i < capacity_; ++i) {
        if (data_[i].value != -1){
            std::cout << data_[i].key << " -> " << data_[i].value << std::endl;
            figure_of_words += data_[i].value;
        }
    }

    std::cout << std::endl << "collisions_ = " << GetCollisions() << std::endl <<
        "There are " << count_ << " unique words" << std::endl <<
        "At all analyzed " << figure_of_words << " words" << std::endl <<
        "Capacity = " << capacity_ << std::endl;
}

HashTable& HashTable::operator=(const HashTable& other) {
    if (this == &other) {
        return *this;
    }

    capacity_ = other.capacity_;
    count_ = other.count_;
    delete[] data_;
    std::copy(other.data_, other.data_ + capacity_, data_);
    return *this;
}

HashTable& HashTable::operator=(HashTable&& other) {
    if (this == &other) {
        return *this;
    }

    capacity_ = other.capacity_;
    count_ = other.count_;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

#endif //HASHTABLE_IMPL_H