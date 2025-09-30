#include "barray_set.hpp"

void BitArraySet::fillSet(bool* other){
    if(!other){
        for(int i=0;i<UNIVERSUM_SIZE;i++){
            set[i]=false;
        }
        return;    
    }
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        set[i]=other[i];
    }
}

BitArraySet::BitArraySet(){
    set = new bool[UNIVERSUM_SIZE];
    fillSet();
}

BitArraySet::BitArraySet(const char* inpSet){
    if(!inpSet){
        set = new bool[UNIVERSUM_SIZE];
        fillSet();
        return;     
    }
    set = new bool[UNIVERSUM_SIZE];
    fillSet();
    for(int i=0;i<strlen(inpSet);i++){
        set[inpSet[i]-'A'] = true;
    }
}

BitArraySet::BitArraySet(const BitArraySet& other){
    set = new bool[UNIVERSUM_SIZE];
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        this->set[i] = other.set[i];
    }
}

BitArraySet::~BitArraySet(){
    delete[] set;
}

BitArraySet& BitArraySet::operator=(const BitArraySet& other){
    if(&other==this){
        return *this;
    }
    this->fillSet(other.set);
    return *this;
}

BitArraySet BitArraySet::operator&(const BitArraySet& other){
    BitArraySet res;
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        res.set[i] = this->set[i] && other.set[i];
    }
    return res;
}

BitArraySet BitArraySet::operator|(const BitArraySet& other){
    BitArraySet res;
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        res.set[i] = this->set[i] || other.set[i];
    }
    return res;
}

BitArraySet& BitArraySet::operator&=(const BitArraySet& other){
    if(&other==this){
        return *this;
    }
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        this->set[i] = this->set[i] && other.set[i];
    }
    return *this;
}

BitArraySet& BitArraySet::operator|=(const BitArraySet& other){
    if(&other==this){
        return *this;
    }
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        this->set[i] = this->set[i] || other.set[i];
    }
    return *this;
}

BitArraySet BitArraySet::operator~(){
    BitArraySet res;
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        res.set[i] = !this->set[i];
    }
    return res;
}

bool BitArraySet::operator==(const BitArraySet& other){
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        if(this->set[i]!=other.set[i]){
            return false;
        }
    }
    return true;
}

void BitArraySet::insert(char ch){
    set[ch-'A'] = true;
}

void BitArraySet::remove(char ch){
    set[ch-'A'] = false;
}

void BitArraySet::print(){
    char* strSet = toChar();
    for(int i=0;i<strlen(strSet);i++){
        std::cout << strSet[i];
        if(i!=strlen(strSet)-1){
            std::cout << ", ";
        }
    }
}

char* BitArraySet::toChar(){
    char* res = new char[UNIVERSUM_SIZE+1];
    int resSize=0;
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        if(set[i]){
            res[resSize] = 'A'+i;
            resSize++;
        }
    }
    res[resSize]='\0';
    return res;
}

std::string BitArraySet::toString(){
    std::string res(toChar());
    return res;
}

void BitArraySet::clear(){
    fillSet();
}