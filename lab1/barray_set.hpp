#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
const int POWER_OF_ALPHABET = 26;

class BitArraySet{
private:
    bool* bits; //bits set array
public:
    BitArraySet(const char* elements); //constructor with parameter (array of chars)
    void addElement(char element); //Function adds element into set array
    std::string toString(); //Function converts a set into a string
    char* toDynChar(); //converting the bit array to array
    BitArraySet subtractSets(const BitArraySet& B, const BitArraySet& C, const BitArraySet& D); //E = A AND NOT(B OR C OR D)
};