#pragma once
#include <iostream>
#include <cstring>
#include <string>

class BitMaskSet{
private:
    unsigned long long set; //set in the form of a bitmask
    static const std::size_t UNIVERSUM_SIZE = 26; //size of latin alphabet
    static int setCounter;
public:
    BitMaskSet(); //default constructor
    BitMaskSet(const char* inpSet); //constructor with the array of characters
    BitMaskSet(const BitMaskSet& other); //copy constructor
    ~BitMaskSet(); //destructor
    BitMaskSet operator|(const BitMaskSet& other)const; //union operator
    BitMaskSet operator&(const BitMaskSet& other)const; //intersection operator
    BitMaskSet& operator=(const BitMaskSet& other); //assignment operator
    BitMaskSet& operator|=(const BitMaskSet& other); //union operator with assignmenet
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