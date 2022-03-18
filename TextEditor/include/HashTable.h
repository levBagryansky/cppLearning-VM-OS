#ifndef HASHTABLE_IMPL_H
#define HASHTABLE_IMPL_H

#include <valarray>
#include <iostream>

const int const_val1 = 37;
const int const_val2 = 3;
const int hash_val = 23;
const int start_capacity = 40e3;

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


#endif //HASHTABLE_IMPL_H