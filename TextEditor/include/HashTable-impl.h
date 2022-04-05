#ifndef HASHTABLE_IMPL_H
#define HASHTABLE_IMPL_H

#include <valarray>
#include <iostream>

const int CONST_VAL1 = 37;
const int CONST_VAL2 = 3;
const int HASH_VAL = 23;
const int START_CAPACITY = 40e3;

template <class KeyT>
class HashTable {
   public:
    HashTable();
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    ~HashTable();
    void AddPair(const KeyT& key, int value);
    size_t Length() const;
    bool HaveKey(const KeyT& key) const;
    int GetValue(const KeyT& key) const;
    int GetCollisions() const;

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;

   protected:
    void Resize();
    size_t HashFunction(const KeyT& key) const;
    size_t GetIndex(const KeyT& key) const;

    struct Item{
        KeyT key;
        int value = -1;
    };

    size_t capacity_; // size of array
    size_t count_ = 0;    // count of items
    Item* data_;
};

template <class KeyT>
HashTable<KeyT>::HashTable()
    : capacity_(START_CAPACITY), data_(new Item[START_CAPACITY]) {}

template <class KeyT>
HashTable<KeyT>::HashTable(const HashTable& other)
    : capacity_(other.capacity_),
      count_(other.count_),
      data_(new Item[other.capacity_]) {
    std::copy(other.data_, other.data_ + capacity_, data_);
}

template <class KeyT>
HashTable<KeyT>::HashTable(HashTable&& other) noexcept
    : capacity_(other.capacity_), count_(other.count_), data_(other.data_) {
    other.data_ = nullptr;
}

template <class KeyT>
HashTable<KeyT>::~HashTable() { delete[] data_; }

template <class KeyT>
size_t HashTable<KeyT>::HashFunction(const KeyT& key) const{
    size_t result = std::hash<KeyT>()(key) % capacity_;
    return result;
}

template <class KeyT>
size_t HashTable<KeyT>::GetIndex(const KeyT& key) const{
    size_t index = HashFunction(key);
    size_t i = 0;
    while (data_[index].value != -1) {
        i++;
        index = (index + CONST_VAL1 * i + CONST_VAL2 * i * i) % capacity_;
    }

    return index;
}

template <class KeyT>
void HashTable<KeyT>::AddPair(const KeyT& key, int value) {
    if (2 * count_ >= capacity_) {
        Resize();
    }

    size_t index = GetIndex(key);

    data_[index].key = key;
    data_[index].value = value;
    count_++;
}

template <class KeyT>
size_t HashTable<KeyT>::Length() const{ return count_; }

template <class KeyT>
void HashTable<KeyT>::Resize(){
    size_t prev_capacity = capacity_;
    capacity_ *= 2;
    Item* prev_data = data_;
    data_ = new Item[capacity_];
    count_ = 0;
    for (size_t i = 0; i < prev_capacity; ++i) {
        if (prev_data[i].value != -1) {
            AddPair(prev_data[i].key, prev_data[i].value);
        }
    }
    delete[] prev_data;
}

template <class KeyT>
bool HashTable<KeyT>::HaveKey(const KeyT& key) const{
    size_t index = HashFunction(key);
    size_t i = 0;
    while (data_[index].value != -1) {
        if (data_[index].key == key) {
            return true;
        }
        i++;
        index = (index + CONST_VAL1 * i + CONST_VAL2 * i * i) % capacity_;
    }

    return false;
}

template <class KeyT>
int HashTable<KeyT>::GetValue(const KeyT& key) const{
    size_t index = HashFunction(key);
    size_t i = 0;
    while (data_[index].value != -1) {
        if (data_[index].key == key) {
            return data_[index].value;
        }
        i++;
        index = (index + CONST_VAL1 * i + CONST_VAL2 * i * i) % capacity_;
    }
    return -1;
}

template <class KeyT>
int HashTable<KeyT>::GetCollisions() const{
    int result = 0;
    for (size_t i = 0; i < capacity_; ++i) {
        if ((data_[i].value != -1) && (i != HashFunction(data_[i].key))) {
            result++;
        }
    }

    return result;
}

template <class KeyT>
HashTable<KeyT>& HashTable<KeyT>::operator=(const HashTable& other) {
    if (this != &other) {
        capacity_ = other.capacity_;
        count_ = other.count_;
        data_ = new Item[capacity_];
        std::copy(other.data_, other.data_ + capacity_, data_);
    }
    return *this;
}

template <class KeyT>
HashTable<KeyT>& HashTable<KeyT>::operator=(HashTable&& other) noexcept {
    if (this != &other) {
        capacity_ = other.capacity_;
        count_ = other.count_;
        data_ = other.data_;
        other.data_ = nullptr;
    }

    return *this;
}

#endif //HASHTABLE_IMPL_H