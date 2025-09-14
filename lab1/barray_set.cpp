#include "barray_set.hpp"

//CONSTRUCTOR//
/*init first element, size of universe
and vector array "bits", false mean array is empty*/
BitArraySet::BitArraySet(const char* elements){
    bits.resize(POWER_OF_ALPHABET, false);
    //entering array elements from the console
    if(elements != nullptr){
        size_t length = strlen(elements);
        if(length > 0){
            for(int i = 0; i < length; i++){
                addElement(elements[i]);
            }
        }
    }
}

//METHODS// 
//Method printing set array to console
void BitArraySet::print(){
    for(int i=0;i<POWER_OF_ALPHABET;i++){
        if(this->bits[i]){
            std::cout << static_cast<char>('A'+i) << ' ';
        }
    }
    std::cout << '\n';
}

void BitArraySet::addElement(char element) {
    int index = element - 'A';
    if (index >= 0 && index < POWER_OF_ALPHABET) {
        bits[index] = true;
    }
}

//Main operation: E = A \ (B ∪ C ∪ D)
BitArraySet BitArraySet::subtractSets(const BitArraySet& B, const BitArraySet& C, const BitArraySet& D){
    BitArraySet result(""); //init empty result array
    for(int i = 0; i < POWER_OF_ALPHABET; i++){
        bool unionBCD = B.bits[i] || C.bits[i] || D.bits[i];//Applies the operation union
        result.bits[i] = this->bits[i] && !unionBCD; //Applies the operations (AND, NOT)
    }
    return result;
}

//Function converts a set into a string
std::string BitArraySet::toString(){
    std::string result;
    for(int i = 0; i < POWER_OF_ALPHABET; i++){
        if(bits[i]){ //bit = 1
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