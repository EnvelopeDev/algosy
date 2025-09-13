#include "bmask_set.hpp"
#include <cstring>

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

BitMask BitMask::unionWith(const BitMask& other) const{
    BitMask result("");
    result.mask = this->mask | other.mask;
    return result;
}

BitMask BitMask::subtract(const BitMask& other){
    BitMask result("");
    result.mask = this->mask & ~other.mask;
    return result;
}

void BitMask::addElement(char element){
    int index = element - 'A';
    if (index >= 0 && index < ALPHABET_SIZE) {
        mask |= (1ULL << index);
    }
}

BitMask BitMask::subtractSets(const BitMask& B, const BitMask& C, const BitMask& D){
    BitMask unionSet = B.unionWith(C).unionWith(D);
    return (*this).subtract(unionSet);
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

void BitMask::print(){
    for(int i=0;i<ALPHABET_SIZE;i++){
        if(mask & (1ULL << i)){
            std::cout << static_cast<char>('A'+i) << ' ';
        }
    }
    std::cout << '\n';
}