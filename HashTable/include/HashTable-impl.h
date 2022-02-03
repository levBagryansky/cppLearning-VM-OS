#ifndef HASHTABLE_IMPL_H
#define HASHTABLE_IMPL_H

template<class T>
class HashTable{
public:

private:
    struct Node{
        T value;
        Node *next;
    };

    size_t capacity_;
    size_t count_;
    Node** data_;
};


#endif HASHTABLE_IMPL_H