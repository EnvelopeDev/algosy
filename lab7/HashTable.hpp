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
public:
    HashTable(const size_t _numBuckets=43);
    ~HashTable();
};

template<typename TK, typename TV>
HashTable<TK, TV>::HashTable(const size_t _numBuckets=43):numBuckets(_numBuckets){
    buckets.resize(numBuckets);
}