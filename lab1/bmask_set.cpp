#include "bmask_set.hpp"

BitMask::BitMask(const char* elements){
    mask=0ULL;
    if(elements != nullptr){
        size_t length = strlen(elements);
        if(length>0){
            for(int i=0; i < length; i++){
                addElement(elements[i]);
            }
        }
    }
}

void BitMask::addElement(char element){
    int index = element - 'A';
    if (index >= 0 && index < ALPHABET_SIZE) {
        mask |= (1ULL << index);
    }
}

BitMask BitMask::subtractSets(const BitMask& B, const BitMask& C, const BitMask& D){
    unsigned long long maskE = this->mask & ~(B.mask | C.mask | D.mask); //E = A AND NOT(B OR C OR D)
    BitMask unionSet("");
    unionSet.mask = maskE;
    return unionSet;
}

std::string BitMask::toString(){
    std::string result;
    for(int i=0; i<ALPHABET_SIZE; i++){
        if (mask & (1ULL << i)) {
            result += 'A' + i;
        }
    }
    return result;
}

char* BitMask::toDynChar(){
    std::string set = this->toString();
    char* res = new char[set.length()+1];
    for(int i=0;i<set.length();i++){
        res[i] = set[i];
    }
    res[set.length()] = '\0';
    return res;
}