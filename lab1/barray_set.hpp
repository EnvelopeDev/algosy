#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

class BitArraySet {
private:
    std::vector<bool> bits; //bits set array
    int universe_size;
    char first_element;
    
public:
    BitArraySet(const char* elements = "", int size = 26, char first = 'A');

    void print() const; //Method printing set array to console

    void addElement(char element); //Function add element into set array
    bool contains(char element) const; //Function for check element existing
    std::string toString() const; //Function converts a set into a string
    static BitArraySet mainOperation(const BitArraySet& A, const BitArraySet& B, 
                                  const BitArraySet& C, const BitArraySet& D); //Main operation: E = A \ (B ∪ C ∪ D)
};