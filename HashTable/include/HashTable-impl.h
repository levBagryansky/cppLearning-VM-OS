#ifndef HASHTABLE_IMPL_H
#define HASHTABLE_IMPL_H

template<class TKey, class TValue>
class HashTable{
public:

private:
    struct Node{
        TKey key;
        TValue value;
        Node *next;
    };

    size_t capacity_;
    size_t count_;
    Node** data_;
};


#endif HASHTABLE_IMPL_H