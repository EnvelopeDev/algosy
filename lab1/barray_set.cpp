#include "barray_set.hpp"

BitArraySet::BitArraySet(const char* elements){
    bits = new bool[POWER_OF_ALPHABET];
    for(int i=0;i<POWER_OF_ALPHABET;i++){
        bits[i]=false;
    }
    //entering array elements (converting from char* to vector<bool>)
    if(elements != nullptr){
        size_t length = strlen(elements);
        if(length > 0){
            for(int i = 0; i < length; i++){
                addElement(elements[i]);
            }
        }
    }
}

void BitArraySet::addElement(char element) {
    int index = element - 'A';
    if (index >= 0 && index < POWER_OF_ALPHABET) {
        bits[index] = true;
    }
}

BitArraySet BitArraySet::subtractSets(const BitArraySet& B, const BitArraySet& C, const BitArraySet& D){
    BitArraySet result(""); //init empty result array
    for(int i = 0; i < POWER_OF_ALPHABET; i++){
        bool unionBCD = B.bits[i] || C.bits[i] || D.bits[i];//applies the operation union
        result.bits[i] = this->bits[i] && !unionBCD; //applies the operations (AND, NOT)
    }
    return result;
}

std::string BitArraySet::toString(){
    std::string result;
    for(int i = 0; i < POWER_OF_ALPHABET; i++){
        if(bits[i]){
            result += 'A' + i; //finding element and add it into string
        }
    }
    return result;
}

char* BitArraySet::toDynChar(){
    std::string set = this->toString();
    char* res = new char[set.length()+1];
    for(int i=0;i<set.length();i++){
        res[i] = set[i];
    }
    res[set.length()] = '\0';
    return res;
}