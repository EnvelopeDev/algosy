#pragma once
#include <iostream>
#include <string>
#include <cstring>

class ArraySet{
private:
    char* set;
    static const std::size_t UNIVERSUM_SIZE = 26;
    std::size_t sz;
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
    void insert(char ch);
    void remove(char ch);
    bool constains(char ch);
    void clear();
};