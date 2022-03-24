#ifndef HASHTABLE_IMPL_H
#define HASHTABLE_IMPL_H

#include <valarray>
#include <iostream>

const int const_val1 = 37;
const int const_val2 = 3;
const int hash_val = 23;
const int start_capacity = 40e3;

template <class Key_T>
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
        Key_T key;
        int value;
        Item(): value(-1){};
    };

    size_t capacity_; // size of array
    size_t count_;    // count of items
    Item* data_;
};

template <class Key_T>
HashTable<Key_T>::HashTable()
    : capacity_(start_capacity), count_(0), data_(new Item[start_capacity]) {}

template <class Key_T>
HashTable<Key_T>::HashTable(const HashTable& other)
    : capacity_(other.capacity_),
      count_(other.count_),
      data_(new Item[other.capacity_]) {
    std::copy(other.data_, other.data_ + capacity_, data_);
}

template <class Key_T>
HashTable<Key_T>::HashTable(HashTable&& other) noexcept
    : capacity_(other.capacity_), count_(other.count_), data_(other.data_) {
    other.data_ = nullptr;
}

template <class Key_T>
HashTable<Key_T>::~HashTable() { delete[] data_; }

template <class Key_T>
size_t HashTable<Key_T>::HashFunction(const std::string& key) {
    size_t result = 0;
    for (uint i = 0; i < key.length(); ++i) {
        result = (result + key[i] * static_cast<size_t>(pow(hash_val, i))) %
                 capacity_;
    }
    //result = std::hash<Key_T>{} (key) % capacity_;
    return result;
}

template <class Key_T>
size_t HashTable<Key_T>::GetIndex(const std::string& key) {
    size_t index = HashFunction(key);
    //size_t index = std::hash<Key_T>{}(key) % capacity_;
    int i = 0;
    while (data_[index].value != -1) {
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }

    return index;
}

template <class Key_T>
void HashTable<Key_T>::AddPair(const std::string& key, int value) {
    if (2 * count_ >= capacity_) {
        Resize();
    }

    size_t index = GetIndex(key);

    data_[index].key = key;
    data_[index].value = value;
    count_++;
}

template <class Key_T>
size_t HashTable<Key_T>::Length() { return count_; }

template <class Key_T>
void HashTable<Key_T>::Resize() {
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

template <class Key_T>
bool HashTable<Key_T>::HaveKey(const std::string& key) {
    size_t index = HashFunction(key);
    int i = 0;
    while (data_[index].value != -1) {
        if (data_[index].key == key) {
            return true;
        }
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }

    return false;
}

template <class Key_T>
int HashTable<Key_T>::GetValue(const std::string& key) {
    size_t index = HashFunction(key);
    int i = 0;
    while (data_[index].value != -1) {
        if (data_[index].key == key) {
            return data_[index].value;
        }
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }
    return -1;
}

template <class Key_T>
int HashTable<Key_T>::GetCollisions() {
    int result = 0;
    for (size_t i = 0; i < capacity_; ++i) {
        if ((data_[i].value != -1) && (i != HashFunction(data_[i].key))) {
            result++;
        }
    }

    return result;
}

template <class Key_T>
void HashTable<Key_T>::Print() {
    int figure_of_words = 0;

    for (size_t i = 0; i < capacity_; ++i) {
        if (data_[i].value != -1) {
            std::cout << data_[i].key << " -> " << data_[i].value << std::endl;
            figure_of_words += data_[i].value;
        }
    }

    std::cout << std::endl
              << "collisions_ = " << GetCollisions() << std::endl
              << "There are " << count_ << " unique words" << std::endl
              << "At all analyzed " << figure_of_words << " words" << std::endl
              << "Capacity = " << capacity_ << std::endl;
}

template <class Key_T>
HashTable<Key_T>& HashTable<Key_T>::operator=(const HashTable& other) {
    if (this != &other) {
        capacity_ = other.capacity_;
        count_ = other.count_;
        data_ = new Item[capacity_];
        std::copy(other.data_, other.data_ + capacity_, data_);
    }
    return *this;
}

template <class Key_T>
HashTable<Key_T>& HashTable<Key_T>::operator=(HashTable&& other) {
    if (this != &other) {
        capacity_ = other.capacity_;
        count_ = other.count_;
        data_ = other.data_;
        other.data_ = nullptr;
    }

    return *this;
}

#endif //HASHTABLE_IMPL_H