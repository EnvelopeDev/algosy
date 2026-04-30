#include "bmask_set.hpp"

int BitMaskSet::setCounter=0;

BitMaskSet::BitMaskSet(){
    set = 0UL;
}

BitMaskSet::BitMaskSet(const char* inpSet){
    set = 0UL;
    if(!inpSet){
        return;     
    }
    unsigned long long mask;
    for(int i=0;i<strlen(inpSet);i++){
        if(inpSet[i]>='A' && inpSet[i]<='Z'){
            mask = 1UL << (inpSet[i]-'A');
        }
        else{
            if(inpSet[i]>'f'){
                continue;
            }
            mask = 1UL << (inpSet[i]-'a'+26);
        }
        set|=mask;
    }
}

BitMaskSet::BitMaskSet(const std::string& inpSet){
    set = 0UL;
    if(inpSet.length()==0){
        return;     
    }
    unsigned long long mask;
    for(int i=0;i<inpSet.length();i++){
        if(inpSet[i]>='A' && inpSet[i]<='Z'){
            mask = 1UL << (inpSet[i]-'A');
        }
        else{
            if(inpSet[i]>'f'){
                continue;
            }
            mask = 1UL << (inpSet[i]-'a'+26);
        }
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
    res.set = ~this->set & ((1UL<<UNIVERSUM_SIZE)-1);
    return res;
}

bool BitMaskSet::operator==(const BitMaskSet& other)const{
    return (this->set == other.set);
}

void BitMaskSet::insert(char ch){
    if(ch>='A' && ch<='Z'){
        set |= 1UL << (ch-'A');
    }
    else{
        if(ch>'f'){
            return;
        }
        set |= 1UL << (ch-'a'+26);
    }
}

BitMaskSet BitMaskSet::subtractSets(const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D)const{
    BitMaskSet resSet = *this & ~(B | C | D);
    return resSet;
}

void BitMaskSet::remove(char ch){
    if(ch>='A' && ch<='Z'){
        set &= ~(1UL << (ch-'A'));
    }
    else{
        if(ch>'f'){
            return;
        }
        set &= ~(1UL << (ch-'a'+26));
    }
}

bool BitMaskSet::contains(char ch)const{
    if(ch>='A' && ch<='Z'){
        return set & (1UL << (ch-'A'));
    }
    if(ch>'f'){
        return false;
    }
    return set & (1UL << (ch-'a'+26));
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
        if(set & (1UL<<i)){
            if(i<26){
                res[resSize] = 'A'+i;
            }
            else{
                res[resSize] = 'a'+i-26;
            }
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
    set = 0UL;
}