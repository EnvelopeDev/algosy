#pragma once
#include <vector>
#include "bmask_set.hpp"

class HashTable
{
private:
    int numBuckets;
    
    unsigned hash(unsigned long num);
public:
    HashTable();
    ~HashTable();
};