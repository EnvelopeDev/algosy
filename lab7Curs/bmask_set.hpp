#pragma once
#include <iostream>
#include <cstring>
#include <string>

class BitMaskSet{
private:
    unsigned long set; //set in the form of a bitmask
    static const std::size_t UNIVERSUM_SIZE = 32; //size of latin alphabet
    static int setCounter;
public:
    BitMaskSet();
    BitMaskSet(const unsigned long _mask);
    BitMaskSet(const char* inpSet);
    BitMaskSet(const std::string& inpSet);
    BitMaskSet(const BitMaskSet& other);
    ~BitMaskSet();

    BitMaskSet& operator=(const BitMaskSet& other);

    BitMaskSet operator|(const BitMaskSet& other)const;   
    BitMaskSet operator&(const BitMaskSet& other)const;   
    BitMaskSet operator^(const BitMaskSet& other)const;   
    BitMaskSet operator-(const BitMaskSet& other)const;   
    BitMaskSet operator~()const;                          

    BitMaskSet& operator|=(const BitMaskSet& other);
    BitMaskSet& operator&=(const BitMaskSet& other);
    BitMaskSet& operator^=(const BitMaskSet& other);
    BitMaskSet& operator-=(const BitMaskSet& other);

    bool operator==(const BitMaskSet& other)const;

    static BitMaskSet variant36(const BitMaskSet& A, const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D, const BitMaskSet& E);

    BitMaskSet subtractSets(const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D)const;

    char* toChar()const;
    std::string toString()const;
    void print()const;
    void insert(char ch);
    void remove(char ch);
    bool contains(char ch)const;
    void clear();
    unsigned long getMask()const;
    void setMask(const unsigned long _mask);
};
