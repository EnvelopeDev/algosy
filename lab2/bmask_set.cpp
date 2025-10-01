#include "bmask_set.hpp"

int BitMaskSet::setCounter=0;

BitMaskSet::BitMaskSet(){
    if(setCounter < 10) std::cout << "BitMaskSet::BitMaskSet() - default constructor" << std::endl;
    set = 0ULL;
    setCounter++;
    if(setCounter < 10) std::cout << "Active BitMaskSet instances: " << setCounter << std::endl;
}

BitMaskSet::BitMaskSet(const char* inpSet){
    if(setCounter < 10) std::cout << "BitMaskSet::BitMaskSet(const char* inpSet) - constructor from char array" << std::endl;
    set = 0ULL;
    if(!inpSet){
        setCounter++;
        if(setCounter < 10) std::cout << "Active BitMaskSet instances: " << setCounter << std::endl;
        return;     
    }
    unsigned long long mask;
    for(int i=0;i<strlen(inpSet);i++){
        mask = 1ULL << (inpSet[i]-'A');
        set|=mask;
    }
    setCounter++;
    if(setCounter < 10) std::cout << "Active BitMaskSet instances: " << setCounter << std::endl;
}

BitMaskSet::BitMaskSet(const BitMaskSet& other){
    if(setCounter < 10) std::cout << "BitMaskSet::BitMaskSet(const BitMaskSet& other) - copy constructor" << std::endl;
    set = other.set;
    setCounter++;
    if(setCounter < 10) std::cout << "Active BitMaskSet instances: " << setCounter << std::endl;
}

BitMaskSet::~BitMaskSet(){
    if(setCounter < 10) std::cout << "BitMaskSet::~BitMaskSet() - destructor" << std::endl;
    setCounter--;
    if(setCounter < 10) std::cout << "Active BitMaskSet instances: " << setCounter << std::endl;
}

BitMaskSet& BitMaskSet::operator=(const BitMaskSet& other){
    if(setCounter < 10) std::cout << "BitMaskSet::operator=(const BitMaskSet& other) - copy assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    this->set = other.set;
    return *this;
}

BitMaskSet BitMaskSet::operator&(const BitMaskSet& other)const{
    if(setCounter < 10) std::cout << "BitMaskSet::operator&(const BitMaskSet& other) - intersection operator" << std::endl;
    BitMaskSet res;
    res.set = this->set&other.set;
    return res;
}

BitMaskSet BitMaskSet::operator|(const BitMaskSet& other)const{
    if(setCounter < 10) std::cout << "BitMaskSet::operator|(const BitMaskSet& other) - union operator" << std::endl;
    BitMaskSet res;
    res.set = this->set|other.set;
    return res;
}

BitMaskSet& BitMaskSet::operator&=(const BitMaskSet& other){
    if(setCounter < 10) std::cout << "BitMaskSet::operator&=(const BitMaskSet& other) - intersection assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    this->set &= other.set;
    return *this;
}

BitMaskSet& BitMaskSet::operator|=(const BitMaskSet& other){
    if(setCounter < 10) std::cout << "BitMaskSet::operator|=(const BitMaskSet& other) - union assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    this->set |= other.set;
    return *this;
}

BitMaskSet BitMaskSet::operator~()const{
    if(setCounter < 10) std::cout << "BitMaskSet::operator~() - complement operator" << std::endl;
    BitMaskSet res;
    res.set = ~this->set & ((1ULL<<UNIVERSUM_SIZE)-1);
    return res;
}

bool BitMaskSet::operator==(const BitMaskSet& other)const{
    if(setCounter < 10) std::cout << "BitMaskSet::operator==(const BitMaskSet& other) - equality operator" << std::endl;
    return (this->set == other.set);
}

void BitMaskSet::insert(char ch){
    if(setCounter < 10) std::cout << "BitMaskSet::insert(char ch) - insert character: " << ch << std::endl;
    set |= 1ULL << (ch-'A');
}

BitMaskSet BitMaskSet::subtractSets(const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D)const{
    if(setCounter < 10) std::cout << "BitMaskSet::subtractSets(const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D) - subtract sets method" << std::endl;
    BitMaskSet resSet = *this & ~(B | C | D);
    return resSet;
}

void BitMaskSet::remove(char ch){
    if(setCounter < 10) std::cout << "BitMaskSet::remove(char ch) - remove character: " << ch << std::endl;
    set &= ~(1ULL << (ch-'A'));
}

bool BitMaskSet::contains(char ch)const{
    if(setCounter < 10) std::cout << "BitMaskSet::contains(char ch) - check contains character: " << ch << std::endl;
    return set & (1ULL << (ch-'A'));
}

void BitMaskSet::print()const{
    if(setCounter < 10) std::cout << "BitMaskSet::print() - print set contents" << std::endl;
    char* strSet = toChar();
    for(int i=0;i<strlen(strSet);i++){
        std::cout << strSet[i];
        if(i!=strlen(strSet)-1){
            std::cout << ", ";
        }
    }
}

char* BitMaskSet::toChar()const{
    if(setCounter < 10) std::cout << "BitMaskSet::toChar() - convert to char array" << std::endl;
    char* res = new char[UNIVERSUM_SIZE+1];
    int resSize=0;
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        if(set & (1ULL<<i)){
            res[resSize] = 'A'+i;
            resSize++;
        }
    }
    res[resSize]='\0';
    return res;
}

std::string BitMaskSet::toString()const{
    if(setCounter < 10) std::cout << "BitMaskSet::toString() - convert to string" << std::endl;
    std::string res(toChar());
    return res;
}

void BitMaskSet::clear(){
    if(setCounter < 10) std::cout << "BitMaskSet::clear() - clear set" << std::endl;
    set = 0ULL;
}