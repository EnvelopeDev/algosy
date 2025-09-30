#pragma once
#include <iostream>
#include <string>
#include <cstring>

class BitArraySet{
private:
    bool* set;
    static const std::size_t UNIVERSUM_SIZE = 26;
    void fillSet(bool* other = nullptr);
public:
    BitArraySet();
    BitArraySet(const char* inpSet);
    BitArraySet(const BitArraySet& other);
    ~BitArraySet();
    BitArraySet operator|(const BitArraySet& other);
    BitArraySet operator&(const BitArraySet& other);
    BitArraySet& operator=(const BitArraySet& other);
    BitArraySet& operator|=(const BitArraySet& other);
    BitArraySet& operator&=(const BitArraySet& other);
    BitArraySet operator~();
    bool operator==(const BitArraySet& other);
    char* toChar();
    std::string toString();
    void print();
    void insert(char ch);
    void remove(char ch);
    bool constains(char ch);
    void clear();
};