#pragma once
#include <iostream>
#include <cstring>
#include <string>

class BitMaskSet{
private:
    unsigned long long set;
    static const std::size_t UNIVERSUM_SIZE = 26;
public:
    BitMaskSet();
    BitMaskSet(const char* inpSet);
    BitMaskSet(const BitMaskSet& other);
    ~BitMaskSet();
    BitMaskSet operator|(const BitMaskSet& other)const;
    BitMaskSet operator&(const BitMaskSet& other)const;
    BitMaskSet& operator=(const BitMaskSet& other);
    BitMaskSet& operator|=(const BitMaskSet& other);
    BitMaskSet& operator&=(const BitMaskSet& other);
    BitMaskSet operator~()const;
    bool operator==(const BitMaskSet& other)const;
    BitMaskSet subtractSets(const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D)const;
    char* toChar()const;
    std::string toString()const;
    void print()const;
    void insert(char ch);
    void remove(char ch);
    bool contains(char ch)const;
    void clear();
};