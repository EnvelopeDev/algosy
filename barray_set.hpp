#pragma once
#include <iostream>
#include <string>
#include <vector>

class BitArraySet {
private:
    std::vector<bool> bits;
    int universe_size;
    char first_element;
    
public:
    BitArraySet(const char* elements = "", int size = 26, char first = 'A');

    void addElement(char element);
    bool contains(char element) const;
    BitArraySet unionWith(const BitArraySet& other) const;
    BitArraySet subtract(const BitArraySet& other) const;
    std::string toString() const;
    void print() const;
    
    static BitArraySet subtractSets(const BitArraySet& A, const BitArraySet& B, 
                                  const BitArraySet& C, const BitArraySet& D);
    
    int size() const;
    char first() const;
};