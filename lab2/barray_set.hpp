#pragma once
#include <iostream>
#include <cstring>
#include <string>

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
    BitArraySet operator|(const BitArraySet& other)const;
    BitArraySet operator&(const BitArraySet& other)const;
    BitArraySet& operator=(const BitArraySet& other);
    BitArraySet& operator|=(const BitArraySet& other);
    BitArraySet& operator&=(const BitArraySet& other);
    BitArraySet operator~()const;
    bool operator==(const BitArraySet& other)const;
    BitArraySet subtractSets(const BitArraySet& B, const BitArraySet& C, const BitArraySet& D)const;
    char* toChar()const;
    std::string toString()const;
    void print()const;
    void insert(char ch);
    void remove(char ch);
    bool contains(char ch)const;
    void clear();
};