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

/*void ArraySet::removeDuplicates(){
    size_t oldSize = sz;
    unsigned long long setMask=getSetBitmask();

    if(oldSize==sz){
        return;
    }
    
    if(set!=nullptr){
        delete[] set;
    }
    
    set = new char[UNIVERSUM_SIZE+1];
    set[sz] = '\0';
    initSetWithBitmask(setMask);
}

void ArraySet::initSetWithBitmask(const unsigned long long setMask){
    unsigned long long mask;
    int currSize=0;
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        mask = 1ULL << i;
        if(setMask & mask){
            set[currSize] = 'A'+i;
            currSize++;
        }
    }
}

unsigned long long ArraySet::getSetBitmask(){
    unsigned long long setMask = 0ULL, mask;
    size_t newSize=0;
    for(int i=0;i<sz;i++){
        mask = 1ULL<<(set[i]-'A');
        if(!(setMask & mask)){
            newSize++;
            setMask |= mask;
        }
    }
    sz = newSize;
    return setMask;
}*/