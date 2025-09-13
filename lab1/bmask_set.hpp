#pragma once
#include <iostream>
#include <string>
const int ALPHABET_SIZE = 26;

class BitMask {
private:
    unsigned long long mask;
public:
    BitMask(const char* elements);
    void addElement(char element);
    BitMask unionWith(const BitMask& other) const;
    BitMask subtract(const BitMask& other);
    std::string toString();
    void print();
    BitMask subtractSets(const BitMask& B, const BitMask& C, const BitMask& D); //E = A \ (B ∪ C ∪ D)
};