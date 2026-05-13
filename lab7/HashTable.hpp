#pragma once
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>

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
    TV& getElem(const TK& key);
    bool contains(const TK& key);
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

    for(auto& elem:buckets[bucketIndex]){
        if(elem.first==key){
            elem.second=value;
            return;
        }
    }

    if(buckets[bucketIndex].empty()){
        buckets[bucketIndex].push_back(std::make_pair(key, value));
    }
}

template<typename TK, typename TV>
TV& HashTable<TK, TV>::getElem(const TK& key){
    if(!contains(key)){
        throw std::invalid_argument("NO SUCH KEY!\n");
    }
    unsigned bcktIndex = getBucketIndex(key);
    TV& value=(*buckets[bcktIndex].begin()).second;
    for(const auto& elem:buckets[bcktIndex]){
        if(elem.first==key){
            value = elem.second;
            break;
        }
    }
    return value;
}

template<typename TK, typename TV>
bool HashTable<TK, TV>::contains(const TK& key){
    unsigned bcktIndex = getBucketIndex(key);
    for(const auto& elem:buckets[bcktIndex]){
        if(elem.first==key){
            return true;
        }
    }
    return false;
}