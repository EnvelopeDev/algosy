#include "bmask_set.hpp"

BitMaskSet::BitMaskSet(){
    set = 0ULL;
}

BitMaskSet::BitMaskSet(const char* inpSet){
    set = 0ULL;
    if(!inpSet){
        return;     
    }
    unsigned long long mask;
    for(int i=0;i<strlen(inpSet);i++){
        mask = 1ULL << (inpSet[i]-'A');
        set|=mask;
    }
}

BitMaskSet::BitMaskSet(const BitMaskSet& other){
    set = other.set;
}

BitMaskSet::~BitMaskSet(){}

BitMaskSet& BitMaskSet::operator=(const BitMaskSet& other){
    if(&other==this){
        return *this;
    }
    this->set = other.set;
    return *this;
}

BitMaskSet BitMaskSet::operator&(const BitMaskSet& other)const{
    BitMaskSet res;
    res.set = this->set&other.set;
    return res;
}

BitMaskSet BitMaskSet::operator|(const BitMaskSet& other)const{
    BitMaskSet res;
    res.set = this->set|other.set;
    return res;
}

BitMaskSet& BitMaskSet::operator&=(const BitMaskSet& other){
    if(&other==this){
        return *this;
    }
    this->set &= other.set;
    return *this;
}

BitMaskSet& BitMaskSet::operator|=(const BitMaskSet& other){
    if(&other==this){
        return *this;
    }
    this->set |= other.set;
    return *this;
}

BitMaskSet BitMaskSet::operator~()const{
    BitMaskSet res;
    res.set = ~this->set & ((1ULL<<UNIVERSUM_SIZE)-1);
    return res;
}

bool BitMaskSet::operator==(const BitMaskSet& other)const{
    return (this->set == other.set);
}

void BitMaskSet::insert(char ch){
    set |= 1ULL << (ch-'A');
}

BitMaskSet BitMaskSet::subtractSets(const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D)const{
    BitMaskSet resSet = *this & ~(B | C | D);
    return resSet;
}

void BitMaskSet::remove(char ch){
    set &= ~(1ULL << (ch-'A'));
}

bool BitMaskSet::contains(char ch)const{
    return set & (1ULL << (ch-'A'));
}

void BitMaskSet::print()const{
    char* strSet = toChar();
    for(int i=0;i<strlen(strSet);i++){
        std::cout << strSet[i];
        if(i!=strlen(strSet)-1){
            std::cout << ", ";
        }
    }
}

char* BitMaskSet::toChar()const{
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
    std::string res(toChar());
    return res;
}

void BitMaskSet::clear(){
    set = 0ULL;
}