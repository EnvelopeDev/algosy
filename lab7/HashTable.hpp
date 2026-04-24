#pragma once

class HashTable
{
private:
    int numBuckets;
    unsigned hash(unsigned long num);
public:
    HashTable();
    ~HashTable();
};