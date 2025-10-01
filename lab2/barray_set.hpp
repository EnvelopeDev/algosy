#pragma once
#include <iostream>
#include <cstring>
#include <string>

class BitArraySet{
private:
    bool* set; //set in the form of a bit array (bool array)
    static const std::size_t UNIVERSUM_SIZE = 26; //size of latin alphabet
    void fillSet(bool* other = nullptr); //filling set with a given values or with zeros
    static int setCounter;
public:
    BitArraySet(); //default constructor
    BitArraySet(const char* inpSet); //constructor with the array of characters
    BitArraySet(const BitArraySet& other); //copy constructor
    ~BitArraySet(); //destructor
    BitArraySet operator|(const BitArraySet& other)const; //union operator
    BitArraySet operator&(const BitArraySet& other)const; //intersection operator
    BitArraySet& operator=(const BitArraySet& other); //assignment operator
    BitArraySet& operator|=(const BitArraySet& other); //union operator with assignmenet
    BitArraySet& operator&=(const BitArraySet& other); //intersection operator with assignmenet
    BitArraySet operator~()const; //inverse operator
    bool operator==(const BitArraySet& other)const; //operator to compare sets
    BitArraySet subtractSets(const BitArraySet& B, const BitArraySet& C, const BitArraySet& D)const; //operation of the subtraction (E = A \ (B ∪ C ∪ D))
    char* toChar()const;//converting BitArraySet object to the character array
    std::string toString()const;//converting BitArraySet object to the stl string
    void print()const;
    void insert(char ch); //adding character to the set
    void remove(char ch); //removing character from the set
    bool contains(char ch)const; //checking if the set contains the character
    void clear(); //clearing set, removing all the elements
};