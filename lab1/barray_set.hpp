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

    void addElement(char element); //Function add element into set array
    bool contains(char element) const; //Function for check element existing
    BitArraySet unionWith(const BitArraySet& other) const; //Function combines sets
    BitArraySet subtract(const BitArraySet& other) const; //Function producing the difference of sets
    std::string toString() const; //Function converts a set into a string
    void print() const; //Method printing set array to console
    
    static BitArraySet subtractSets(const BitArraySet& A, const BitArraySet& B, 
                                  const BitArraySet& C, const BitArraySet& D); //Main operation: E = A \ (B ∪ C ∪ D)

};