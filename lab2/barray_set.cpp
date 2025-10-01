#include "barray_set.hpp"

int BitArraySet::setCounter = 0;

void BitArraySet::fillSet(bool* other){
    if(setCounter < 10) std::cout << "BitArraySet::fillSet(bool* other) - fill set from bool array" << std::endl;
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
    if(setCounter < 10) std::cout << "BitArraySet::BitArraySet() - default constructor" << std::endl;
    set = new bool[UNIVERSUM_SIZE];
    fillSet();
    setCounter++;
    if(setCounter < 10) std::cout << "Active BitArraySet instances: " << setCounter << std::endl;
}

BitArraySet::BitArraySet(const char* inpSet){
    if(setCounter < 10) std::cout << "BitArraySet::BitArraySet(const char* inpSet) - constructor from char array" << std::endl;
    if(!inpSet){
        set = new bool[UNIVERSUM_SIZE];
        fillSet();
        setCounter++;
        if(setCounter < 10) std::cout << "Active BitArraySet instances: " << setCounter << std::endl;
        return;     
    }
    set = new bool[UNIVERSUM_SIZE];
    fillSet();
    for(int i=0;i<strlen(inpSet);i++){
        set[inpSet[i]-'A'] = true;
    }
    setCounter++;
    if(setCounter < 10) std::cout << "Active BitArraySet instances: " << setCounter << std::endl;
}

BitArraySet::BitArraySet(const BitArraySet& other){
    if(setCounter < 10) std::cout << "BitArraySet::BitArraySet(const BitArraySet& other) - copy constructor" << std::endl;
    set = new bool[UNIVERSUM_SIZE];
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        this->set[i] = other.set[i];
    }
    setCounter++;
    if(setCounter < 10) std::cout << "Active BitArraySet instances: " << setCounter << std::endl;
}

BitArraySet::~BitArraySet(){
    if(setCounter < 10) std::cout << "BitArraySet::~BitArraySet() - destructor" << std::endl;
    delete[] set;
    setCounter--;
    if(setCounter < 10) std::cout << "Active BitArraySet instances: " << setCounter << std::endl;
}

BitArraySet& BitArraySet::operator=(const BitArraySet& other){
    if(setCounter < 10) std::cout << "BitArraySet::operator=(const BitArraySet& other) - copy assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    this->fillSet(other.set);
    return *this;
}

BitArraySet BitArraySet::operator&(const BitArraySet& other)const{
    if(setCounter < 10) std::cout << "BitArraySet::operator&(const BitArraySet& other) - intersection operator" << std::endl;
    BitArraySet res;
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        res.set[i] = this->set[i] && other.set[i];
    }
    return res;
}

BitArraySet BitArraySet::operator|(const BitArraySet& other)const{
    if(setCounter < 10) std::cout << "BitArraySet::operator|(const BitArraySet& other) - union operator" << std::endl;
    BitArraySet res;
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        res.set[i] = this->set[i] || other.set[i];
    }
    return res;
}

BitArraySet& BitArraySet::operator&=(const BitArraySet& other){
    if(setCounter < 10) std::cout << "BitArraySet::operator&=(const BitArraySet& other) - intersection assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        this->set[i] = this->set[i] && other.set[i];
    }
    return *this;
}

BitArraySet& BitArraySet::operator|=(const BitArraySet& other){
    if(setCounter < 10) std::cout << "BitArraySet::operator|=(const BitArraySet& other) - union assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        this->set[i] = this->set[i] || other.set[i];
    }
    return *this;
}

BitArraySet BitArraySet::operator~()const{
    if(setCounter < 10) std::cout << "BitArraySet::operator~() - complement operator" << std::endl;
    BitArraySet res;
    
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        res.set[i] = !this->set[i];
    }
    return res;
}

bool BitArraySet::operator==(const BitArraySet& other)const{
    if(setCounter < 10) std::cout << "BitArraySet::operator==(const BitArraySet& other) - equality operator" << std::endl;
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        if(this->set[i]!=other.set[i]){
            return false;
        }
    }
    return true;
}

void BitArraySet::insert(char ch){
    if(setCounter < 10) std::cout << "BitArraySet::insert(char ch) - insert character: " << ch << std::endl;
    set[ch-'A'] = true;
}

BitArraySet BitArraySet::subtractSets(const BitArraySet& B, const BitArraySet& C, const BitArraySet& D)const{
    if(setCounter < 10) std::cout << "BitArraySet::subtractSets(const BitArraySet& B, const BitArraySet& C, const BitArraySet& D) - subtract sets method" << std::endl;
    BitArraySet resSet = *this & ~(B | C | D);
    return resSet;
}

void BitArraySet::remove(char ch){
    if(setCounter < 10) std::cout << "BitArraySet::remove(char ch) - remove character: " << ch << std::endl;
    set[ch-'A'] = false;
}

bool BitArraySet::contains(char ch)const{
    if(setCounter < 10) std::cout << "BitArraySet::contains(char ch) - check contains character: " << ch << std::endl;
    return set[ch-'A'];
}

void BitArraySet::print()const{
    if(setCounter < 10) std::cout << "BitArraySet::print() - print set contents" << std::endl;
    char* strSet = toChar();
    for(int i=0;i<strlen(strSet);i++){
        std::cout << strSet[i];
        if(i!=strlen(strSet)-1){
            std::cout << ", ";
        }
    }
}

char* BitArraySet::toChar()const{
    if(setCounter < 10) std::cout << "BitArraySet::toChar() - convert to char array" << std::endl;
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

std::string BitArraySet::toString()const{
    if(setCounter < 10) std::cout << "BitArraySet::toString() - convert to string" << std::endl;
    std::string res(toChar());
    return res;
}

void BitArraySet::clear(){
    if(setCounter < 10) std::cout << "BitArraySet::clear() - clear set" << std::endl;
    fillSet();
}