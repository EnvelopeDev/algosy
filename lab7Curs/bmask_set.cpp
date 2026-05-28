#include "bmask_set.hpp"

int BitMaskSet::setCounter = 0;

BitMaskSet::BitMaskSet(){ set = 0UL; }
BitMaskSet::BitMaskSet(const unsigned long _mask){ set = _mask; }

BitMaskSet::BitMaskSet(const char* inpSet){
    set = 0UL;
    if(!inpSet) return;
    for(size_t i = 0; i < strlen(inpSet); i++){
        if(inpSet[i] >= 'A' && inpSet[i] <= 'Z')
            set |= 1UL << (inpSet[i] - 'A');
        else if(inpSet[i] >= 'a' && inpSet[i] <= 'f')
            set |= 1UL << (inpSet[i] - 'a' + 26);
    }
}

BitMaskSet::BitMaskSet(const std::string& inpSet){
    set = 0UL;
    for(size_t i = 0; i < inpSet.length(); i++){
        if(inpSet[i] >= 'A' && inpSet[i] <= 'Z')
            set |= 1UL << (inpSet[i] - 'A');
        else if(inpSet[i] >= 'a' && inpSet[i] <= 'f')
            set |= 1UL << (inpSet[i] - 'a' + 26);
    }
}

BitMaskSet::BitMaskSet(const BitMaskSet& other){ set = other.set; }
BitMaskSet::~BitMaskSet(){}

BitMaskSet& BitMaskSet::operator=(const BitMaskSet& other){
    if(this != &other) set = other.set;
    return *this;
}

BitMaskSet BitMaskSet::operator|(const BitMaskSet& other)const{
    return BitMaskSet(set | other.set);
}

BitMaskSet BitMaskSet::operator&(const BitMaskSet& other)const{
    return BitMaskSet(set & other.set);
}

BitMaskSet BitMaskSet::operator^(const BitMaskSet& other)const{
    return BitMaskSet(set ^ other.set);
}

BitMaskSet BitMaskSet::operator-(const BitMaskSet& other)const{
    return BitMaskSet(set & ~other.set);
}

BitMaskSet BitMaskSet::operator~()const{
    return BitMaskSet(~set & static_cast<unsigned long>((1ULL << UNIVERSUM_SIZE) - 1ULL));
}

BitMaskSet& BitMaskSet::operator|=(const BitMaskSet& other){ set |= other.set; return *this; }
BitMaskSet& BitMaskSet::operator&=(const BitMaskSet& other){ set &= other.set; return *this; }
BitMaskSet& BitMaskSet::operator^=(const BitMaskSet& other){ set ^= other.set; return *this; }
BitMaskSet& BitMaskSet::operator-=(const BitMaskSet& other){ set &= ~other.set; return *this; }

bool BitMaskSet::operator==(const BitMaskSet& other)const{ return set == other.set; }


BitMaskSet BitMaskSet::variant36(const BitMaskSet& A, const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D,const BitMaskSet& E)
{
    BitMaskSet tmp1 = B & C;        
    BitMaskSet tmp2 = A ^ tmp1;     
    BitMaskSet tmp3 = tmp2 - D;     
    BitMaskSet result = tmp3 & E;   
    return result;
}

BitMaskSet BitMaskSet::subtractSets(const BitMaskSet& B, const BitMaskSet& C, const BitMaskSet& D)const{
    return *this & ~(B | C | D);
}

char* BitMaskSet::toChar()const{
    char* res = new char[UNIVERSUM_SIZE + 1];
    int resSize = 0;
    for(size_t i = 0; i < UNIVERSUM_SIZE; i++){
        if(set & (1UL << i)){
            res[resSize++] = (i < 26) ? ('A' + i) : ('a' + i - 26);
        }
    }
    res[resSize] = '\0';
    return res;
}

std::string BitMaskSet::toString()const{
    char* c = toChar();
    std::string s(c);
    delete[] c;
    return s;
}

void BitMaskSet::print()const{
    char* s = toChar();
    std::cout << "{";
    for(size_t i = 0; i < strlen(s); i++){
        if(i > 0) std::cout << ", ";
        std::cout << s[i];
    }
    std::cout << "}";
    delete[] s;
}

void BitMaskSet::insert(char ch){
    if(ch >= 'A' && ch <= 'Z')      set |= 1UL << (ch - 'A');
    else if(ch >= 'a' && ch <= 'f') set |= 1UL << (ch - 'a' + 26);
}

void BitMaskSet::remove(char ch){
    if(ch >= 'A' && ch <= 'Z')      set &= ~(1UL << (ch - 'A'));
    else if(ch >= 'a' && ch <= 'f') set &= ~(1UL << (ch - 'a' + 26));
}

bool BitMaskSet::contains(char ch)const{
    if(ch >= 'A' && ch <= 'Z')      return set & (1UL << (ch - 'A'));
    if(ch >= 'a' && ch <= 'f')      return set & (1UL << (ch - 'a' + 26));
    return false;
}

void BitMaskSet::clear(){ set = 0UL; }
unsigned long BitMaskSet::getMask()const{ return set; }
void BitMaskSet::setMask(const unsigned long _mask){ set = _mask; }
