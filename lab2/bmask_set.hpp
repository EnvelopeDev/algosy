#pragma once
#include <iostream>
#include <string>
#include <cstring>

class BitMaskSet{
private:
    unsigned long long set;
    static const std::size_t UNIVERSUM_SIZE = 26;
public:
    BitMaskSet();
    BitMaskSet(const char* inpSet);
    BitMaskSet(const BitMaskSet& other);
    ~BitMaskSet();
    BitMaskSet operator|(const BitMaskSet& other);
    BitMaskSet operator&(const BitMaskSet& other);
    BitMaskSet& operator=(const BitMaskSet& other);
    BitMaskSet& operator|=(const BitMaskSet& other);
    BitMaskSet& operator&=(const BitMaskSet& other);
    BitMaskSet operator~();
    bool operator==(const BitMaskSet& other);
    char* toChar();
    std::string toString();
    void print();
    void insert(char ch);
    void remove(char ch);
    bool constains(char ch);
    void clear();
};