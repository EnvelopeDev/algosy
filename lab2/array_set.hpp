#pragma once
#include <iostream>
#include <cstring>
#include <string>

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
    ArraySet operator|(const ArraySet& other)const;
    ArraySet operator&(const ArraySet& other)const;
    ArraySet& operator=(const ArraySet& other);
    ArraySet& operator|=(const ArraySet& other);
    ArraySet& operator&=(const ArraySet& other);
    ArraySet operator~()const;
    bool operator==(const ArraySet& other)const;
    ArraySet subtractSets(const ArraySet& B, const ArraySet& C, const ArraySet& D)const;
    std::size_t getSize()const;
    char* toChar()const;
    std::string toString()const;
    void print()const;
    void insert(char ch);
    void remove(char ch);
    bool contains(char ch)const;
    void clear();
};