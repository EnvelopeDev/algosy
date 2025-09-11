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
//Function producing the difference of sets
BitArraySet BitArraySet::subtract(const BitArraySet& other) const {
    BitArraySet result("", universe_size, first_element); //init empty result array
    for(int i = 0; i < universe_size; i++){
        result.bits[i] = this->bits[i] && !other.bits[i]; //Applies the operations (∧ and ¬)
    }
    return result;
}

//Function combines sets
BitArraySet BitArraySet::unionWith(const BitArraySet& other) const {
    BitArraySet result("", universe_size, first_element); //init empty result array
    for(int i = 0; i < universe_size; i++){
        result.bits[i] = this->bits[i] || other.bits[i]; //Applies the operation ∪
    }
    return result;
}

//Function add element into set array
void BitArraySet::addElement(char element) {
    int index = element - first_element; //Calculating the index in a bit array
    if(index >= 0 && index < universe_size){ //checking the index for out of range
        bits[index] = true; //sets 1 or 0 into element
    }
}

//Function for check element existing
bool BitArraySet::contains(char element) const {
    int index = element - first_element; //Calculating the index
    if(index >= 0 && index < universe_size){ //checking the index for out of range
        return bits[index]; 
    }
    return false; //If element is outside the universe, it is definitely not in the set
}

//Main operation: E = A \ (B ∪ C ∪ D)
BitArraySet BitArraySet::subtractSets(const BitArraySet& A, const BitArraySet& B, 
                                    const BitArraySet& C, const BitArraySet& D) {
    BitArraySet unionSet = B.unionWith(C).unionWith(D); //Calculating B ∪ C ∪ D
    return A.subtract(unionSet); //Calculating A \ (B ∪ C ∪ D) and return result
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
