#include "barray_set.hpp"

//CONSTRUCTOR//
/*init first element, size of universe
and vector array "bits", false mean array is empty*/
BitArraySet::BitArraySet(const char* elements, int size, char first) 
    : universe_size(size), first_element(first) {
    bits.resize(universe_size, false);
    //entering array elements from the console
    if(elements != nullptr){
        size_t length = strlen(elements);
        if(length > 0){
            for(size_t i = 0; i < length; i++){
                addElement(elements[i]);
            }
        }
    }
}

//METHODS// 
//Method printing set array to console
void BitArraySet::print() const {
    std::cout << toString(); 
}

//FUNCTIONS//
//Function for check element existing
bool BitArraySet::contains(char element) const {
    int index = element - first_element; //Calculating the index
    if(index >= 0 && index < universe_size){ //checking the index for out of range
        return bits[index]; 
    }
    return false; //If element is outside the universe, it is definitely not in the set
}

//Main operation: E = A \ (B ∪ C ∪ D)
BitArraySet BitArraySet::mainOperation(const BitArraySet& A, const BitArraySet& B, 
                                    const BitArraySet& C, const BitArraySet& D) {
    BitArraySet result("", A.universe_size, A.first_element); //init empty result array   
    for(int i = 0; i < A.universe_size; i++){
        bool unionBCD = B.bits[i] || C.bits[i] || D.bits[i];//Applies the operation ∪
        result.bits[i] = A.bits[i] && !unionBCD; //Applies the operations (∧ and ¬)
    }
    return result;
}

//Function converts a set into a string
std::string BitArraySet::toString() const {
    std::string result;
    for(int i = 0; i < universe_size; i++){
        if(bits[i]){ //bit = 1
            result += first_element + i; //finding element and add it into string
        }
    }
    return result;
}