#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
const int POWER_OF_ALPHABET = 26;

class BitArraySet{
private:
    std::vector<bool> bits; //bits set array
public:
    BitArraySet(const char* elements);
    void print(); //Method printing set array to console
    void addElement(char element); //Function add element into set array
    std::string toString(); //Function converts a set into a string
    BitArraySet subtractSets(const BitArraySet& B, const BitArraySet& C, const BitArraySet& D); //Operation of subtracting : E = A XOR (B OR C OR D)
};