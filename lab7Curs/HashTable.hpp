#pragma once
#include <vector>
#include <list>
#include <functional>
#include <iterator>
#include <stdexcept>

#include "bmask_set.hpp"

template<typename TK, typename TV>
class HashTable
{
private:
    size_t numBuckets;
    size_t numElems;
    std::vector<std::list<std::pair<TK, TV>>> buckets; 
    std::hash<TK> hasher;
    unsigned getBucketIndex(const TK& key);
public:
    HashTable(const size_t _numBuckets=43);
    HashTable(const HashTable& other);
    ~HashTable();

    HashTable& operator=(const HashTable& other);
    TV& operator[](const TK& key);
    void insert(const TK& key, const TV& value);
    TV& getElem(const TK& key);
    bool contains(const TK& key);
    void erase(const TK& key);
    void printAllValues();

    size_t getNumElems();
    size_t getNumBuckets();

    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = std::pair<const TK, TV>;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type*;
        using reference         = value_type&;
 
    private:
        using BucketVec  = std::vector<std::list<std::pair<TK, TV>>>;
        using BucketIter = typename BucketVec::iterator;
        using ElemIter   = typename std::list<std::pair<TK, TV>>::iterator;
 
        BucketVec* buckets;
        BucketIter bucketIt;  
        ElemIter   elemIt;    
 
        void skipEmpty() {
            while (bucketIt != buckets->end() && bucketIt->empty()) {
                ++bucketIt;
            }
            if (bucketIt != buckets->end()) {
                elemIt = bucketIt->begin();
            }
        }
 
    public:
        Iterator(BucketVec* bkts, BucketIter bIt)
            : buckets(bkts), bucketIt(bIt)
        {
            skipEmpty();
        }
 
        Iterator(BucketVec* bkts, BucketIter bIt, ElemIter eIt)
            : buckets(bkts), bucketIt(bIt), elemIt(eIt) {}
 
        reference operator*() {
           
            return reinterpret_cast<reference>(*elemIt);
        }
 
        pointer operator->() {
            return reinterpret_cast<pointer>(&(*elemIt));
        }
 
        Iterator& operator++() {
            ++elemIt;
            if (elemIt == bucketIt->end()) {
                ++bucketIt;
                skipEmpty();
            }
            return *this;
        }
 
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
 
        bool operator==(const Iterator& other) const {
            if (bucketIt != other.bucketIt) return false;
            if (bucketIt == buckets->end()) return true;
            return elemIt == other.elemIt;
        }
 
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin(){
        return Iterator(&buckets, buckets.begin());
    }
 
    Iterator end(){
        return Iterator(&buckets, buckets.end(), {});
    }
};

template<typename TK, typename TV>
HashTable<TK, TV>::~HashTable(){}

template<typename TK, typename TV>
HashTable<TK, TV>::HashTable(const size_t _numBuckets):numBuckets(_numBuckets){
    buckets.resize(numBuckets);
    numElems=0;
}

template<typename TK, typename TV>
HashTable<TK, TV>::HashTable(const HashTable& other){
    numBuckets=other.numBuckets;
    buckets.resize(numBuckets);
    numElems=other.numElems;
    auto iter = buckets.begin();
    for(const auto& bucket:other.buckets){
        *iter = bucket;
        iter++;
    }
}

template<typename TK, typename TV>
TV& HashTable<TK, TV>::operator[](const TK& key){
    unsigned bucketIndex = getBucketIndex(key);

    for(auto& elem:buckets[bucketIndex]){
        if(elem.first == key){
            return elem.second;
        }
    }
    
    buckets[bucketIndex].push_back(std::make_pair(key, TV()));
    numElems++;
    
    return buckets[bucketIndex].back().second;
}

template<typename TK, typename TV>
HashTable<TK, TV>& HashTable<TK, TV>::operator=(const HashTable& other){
    if(this==&other){
        return *this;
    }
    
    numBuckets = other.numBuckets;
    numElems = other.numElems;
    hasher = other.hasher;
    
    buckets.clear();
    buckets.resize(numBuckets);
    
    for (size_t i=0; i<numBuckets; i++) {
        buckets[i] = other.buckets[i];
    }
    
    return *this;
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

    buckets[bucketIndex].push_back(std::make_pair(key, value));
    numElems++;
}

template<typename TK, typename TV>
TV& HashTable<TK, TV>::getElem(const TK& key){
    unsigned idx = getBucketIndex(key);
    for(auto& elem:buckets[idx]){
        if(elem.first==key){
            return elem.second;
        }
    }
    throw std::invalid_argument("NO SUCH KEY!\n"); // never reached
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

template<typename TK, typename TV>
void HashTable<TK, TV>::erase(const TK& key){
    if(!contains(key)){
        throw std::invalid_argument("NO SUCH KEY!\n");
    }

    unsigned bcktIndex = getBucketIndex(key);
    auto iter = buckets[bcktIndex].begin();
    auto endIter = buckets[bcktIndex].end();
    while(iter!=endIter){
        if((*iter).first==key){
            buckets[bcktIndex].erase(iter);
            numElems--;
            return;
        }
        iter++;
    }
}

template<typename TK, typename TV>
void HashTable<TK, TV>::printAllValues(){
    int i=0;
    for(const auto& bucket:buckets){
        if(!bucket.empty()){
            std::cout << "BUCKET INDEX: " << i << '\n';
            for(const auto& elem:bucket){
                std::cout << "Key: " << elem.first << ", Value: " << elem.second << "; ";
            }
            std::cout << '\n';
            std::cout << '\n';
        }
        i++;
    }
}

template<typename TK, typename TV>
size_t HashTable<TK, TV>::getNumBuckets(){return numBuckets;}

template<typename TK, typename TV>
size_t HashTable<TK, TV>::getNumElems(){return numElems;}