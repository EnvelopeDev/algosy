#pragma once
#include <iostream>
#include <string>
#include <cstring>
const int ALPHABET_SIZE = 26;

class BitMask {
private:
    unsigned long long mask;
public:
    BitMask(const char* elements); //constructor with parameter (array of chars)
    void addElement(char element); //Function adds element into set
    std::string toString(); //Function converts a set into a string
    char* toDynChar(); //converting the bit mask to array
    BitMask subtractSets(const BitMask& B, const BitMask& C, const BitMask& D); //E = A AND NOT(B OR C OR D)
};