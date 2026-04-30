#pragma once
#include <vector>
#include <list>
#include "bmask_set.hpp"

class HashTable
{
private:
    int numBuckets;
    std::vector<std::list<std::pair<unsigned, BitMaskSet>>> buckets; //Вектор со списками в каждом из которых хранятся пары ключ-значение
    unsigned hash(const BitMaskSet& set);
public:
    HashTable();
    ~HashTable();
};