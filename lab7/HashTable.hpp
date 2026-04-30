#pragma once
#include <vector>
#include <list>
#include <functional>

#include "bmask_set.hpp"

template<typename TK, typename TV>
class HashTable
{
private:
    int numBuckets;
    std::vector<std::list<std::pair<TK, TV>>> buckets; //Вектор со списками в каждом из которых хранятся пары ключ-значение
    std::hash<TK> hasher;
    unsigned getBucketIndex(const TK& key);
public:
    HashTable(const size_t _numBuckets=43);
    ~HashTable();

    void insert(const TK& key, const TV& value);
};

template<typename TK, typename TV>
HashTable<TK, TV>::~HashTable(){}

template<typename TK, typename TV>
HashTable<TK, TV>::HashTable(const size_t _numBuckets):numBuckets(_numBuckets){
    buckets.resize(numBuckets);
}

template<typename TK, typename TV>
unsigned HashTable<TK, TV>::getBucketIndex(const TK& key){
    return hasher(key)%numBuckets;
}

template<typename TK, typename TV>
void HashTable<TK, TV>::insert(const TK& key, const TV& value){
    unsigned bucketIndex = getBucketIndex(key);
    buckets[bucketIndex].push_back();
}