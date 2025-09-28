#include "array_set.hpp"

char* subtractionSets(const char* A, const char* B, const char* C, const char* D) {
    char* res = new char[strlen(A)+1]; //memory allocation for result set
    int resK = 0; //resulting array size
    bool flag = true; //flag to check if an element of set A is not contained in sets B, C, D
    
    for (int i = 0; i < strlen(A); i++) {
        //checking if element of set A is contained in set B
        for(int j = 0; j < strlen(B) && flag; j++) {
            if(A[i] == B[j]) {
                flag = false;
            }
        }
        //checking if element of set A is contained in set C
        for(int j = 0; j < strlen(C) && flag; j++) {
            if(A[i] == C[j]) {
                flag = false;
            }
        }
        //checking if element of set A is contained in set D
        for(int j = 0; j < strlen(D) && flag; j++) {
            if(A[i] == D[j]) {
                flag = false;
            }
        }
        //if an element of set A is not contained in other sets, it`s added to resulting set
        if(flag) {
            res[resK] = A[i];
            resK++;
        }
        flag = true;
    }
    
    res[resK] = '\0'; //adding terminal zero to the end of array
    return res;
}


ArraySet::ArraySet(){
    sz=0;
    set = new char[UNIVERSUM_SIZE+1];
    set[0]='\0';
}

ArraySet::ArraySet(const char* inpSet){
    if(!inpSet){
        sz=0;
        set = new char[UNIVERSUM_SIZE+1];
        set[0]='\0';
        return;     
    }
    sz=strlen(inpSet);
    set = new char[sz+1];
    strcpy(set, inpSet);
    removeDuplicates();
}

ArraySet::ArraySet(const ArraySet& other){
    sz=other.sz;
    set = new char[UNIVERSUM_SIZE+1];
    strcpy(set, other.set);
}

ArraySet::~ArraySet(){
    delete[] set;
}

void ArraySet::removeDuplicates(){
    size_t oldSize = sz;
    unsigned long long setMask=getSetBitmask();

    if(oldSize==sz){
        return;
    }
    
    if(set!=nullptr){
        delete[] set;
    }
    
    set = new char[UNIVERSUM_SIZE+1];
    set[sz] = '\0';
    initSetWithBitmask(setMask);
}

void ArraySet::initSetWithBitmask(const unsigned long long setMask){
    unsigned long long mask;
    int currSize=0;
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        mask = 1ULL << i;
        if(setMask & mask){
            set[currSize] = 'A'+i;
            currSize++;
        }
    }
}

unsigned long long ArraySet::getSetBitmask(){
    unsigned long long setMask = 0ULL, mask;
    size_t newSize=0;
    for(int i=0;i<sz;i++){
        mask = 1ULL<<(set[i]-'A');
        if(!(setMask & mask)){
            newSize++;
            setMask |= mask;
        }
    }
    sz = newSize;
    return setMask;
}

ArraySet& ArraySet::operator=(const ArraySet& other){
    if(&other==this){
        return *this;
    }
    sz=other.sz;
    strcpy(set, other.set);
    return *this;
}

ArraySet ArraySet::operator&(const ArraySet& other){
    ArraySet res;
    bool flag;
    
    for(int i=0;i<this->sz;i++){
        flag = false;
        for(int j=0;j<other.sz && !flag;j++){
            if(this->set[i]==other.set[j]){
                flag = true;
            }
        }
        if(flag){
            res.insert(this->set[i]);
        }
    }

    return res;
}

ArraySet ArraySet::operator|(const ArraySet& other){
    ArraySet res;
    res = *this;
    for(int i=0;i<other.sz;i++){
        res.insert(other.set[i]);
    }
    return res;
}

ArraySet& ArraySet::operator&=(const ArraySet& other){
    if(&other==this){
        return *this;
    }
    


    return *this;
}

ArraySet& ArraySet::operator|=(const ArraySet& other){
    if(&other==this){
        return *this;
    }
    


    return *this;
}

ArraySet ArraySet::operator~(){
    ArraySet res;
    bool flag;
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        flag=true;
        for(int j=0;j<sz&&flag;j++){
            if('A'+i==set[j]){
                flag=false;
            }
        }
        if(flag){
            res.insert('A'+i);
        }
    }
    return res;
}

void ArraySet::insert(char ch){
    if(sz==26){
        return;
    }

    bool flag=true;
    for(int i=0;i<sz && flag;i++){
        if(set[i]==ch){
            flag=false;
        }
    }
    if(flag){
        set[sz]=ch;
        sz++;
        set[sz]='\0';
    }
}

void ArraySet::print(){
    for(int i=0;i<sz;i++){
        std::cout << set[i];
        if(i!=sz-1){
            std::cout << ", ";
        }
    }
}

char* ArraySet::toChar(){
    char* res = new char[sz+1];
    strcpy(res, set);
    return res;
}

std::string ArraySet::toString(){
    std::string res(set);
    return res;
}

std::size_t ArraySet::getSize(){
    return sz;
}