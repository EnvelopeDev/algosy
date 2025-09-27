#pragma once
#include <iostream>
#include <string>
#include <cstring>

//function that subtracts sets B, C, D from set A
char* subtractionSets(const char* A, const char* B, const char* C, const char* D);

class ArraySet{
private:
    char* set;
    static const std::size_t UNIVERSUM_SIZE = 26;
    std::size_t sz;
    void removeDuplicates();
    void initSetWithBitmask(const unsigned long long mask);
    unsigned long long getSetBitmask();
public:
    ArraySet();
    ArraySet(const char* inpSet);
    ArraySet(const ArraySet& other);
    ~ArraySet();
    ArraySet operator|(const ArraySet& other);
    ArraySet operator&(const ArraySet& other);
    ArraySet& operator=(const ArraySet& other);
    ArraySet& operator|=(const ArraySet& other);
    ArraySet& operator&=(const ArraySet& other);
    ArraySet operator~();
    bool operator==(const ArraySet& other);
    std::size_t getSize();
    char* toChar();
    std::string toString();
    void print();
    void insert();
};