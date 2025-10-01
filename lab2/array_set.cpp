#include "array_set.hpp"

int ArraySet::setCounter = 0;

ArraySet::ArraySet(){
    if(setCounter < 10) std::cout << "ArraySet::ArraySet() - default constructor" << std::endl;
    sz=0;
    set = new char[UNIVERSUM_SIZE+1];
    set[0]='\0';
    setCounter++;
    if(setCounter < 10) std::cout << "Active ArraySet instances: " << setCounter << std::endl;
}

ArraySet::ArraySet(const char* inpSet){
    if(setCounter < 10) std::cout << "ArraySet::ArraySet(const char* inpSet) - constructor from char array" << std::endl;
    if(!inpSet){
        sz=0;
        set = new char[UNIVERSUM_SIZE+1];
        set[0]='\0';
        setCounter++;
        if(setCounter < 10) std::cout << "Active ArraySet instances: " << setCounter << std::endl;
        return;     
    }
    sz=0;
    set = new char[UNIVERSUM_SIZE+1];
    for(int i=0;i<strlen(inpSet);i++){
        insert(inpSet[i]);
    }
    set[sz]='\0';
    setCounter++;
    if(setCounter < 10) std::cout << "Active ArraySet instances: " << setCounter << std::endl;
}

ArraySet::ArraySet(const ArraySet& other){
    if(setCounter < 10) std::cout << "ArraySet::ArraySet(const ArraySet& other) - copy constructor" << std::endl;
    sz=other.sz;
    set = new char[UNIVERSUM_SIZE+1];
    strcpy(set, other.set);
    setCounter++;
    if(setCounter < 10) std::cout << "Active ArraySet instances: " << setCounter << std::endl;
}

ArraySet::~ArraySet(){
    if(setCounter < 10) std::cout << "ArraySet::~ArraySet() - destructor" << std::endl;
    delete[] set;
    setCounter--;
    if(setCounter < 10) std::cout << "Active ArraySet instances: " << setCounter << std::endl;
}

ArraySet& ArraySet::operator=(const ArraySet& other){
    if(setCounter < 10) std::cout << "ArraySet::operator=(const ArraySet& other) - copy assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    sz=other.sz;
    strcpy(set, other.set);
    return *this;
}

ArraySet ArraySet::operator&(const ArraySet& other)const{
    if(setCounter < 10) std::cout << "ArraySet::operator&(const ArraySet& other) - intersection operator" << std::endl;
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

ArraySet ArraySet::operator|(const ArraySet& other)const{
    if(setCounter < 10) std::cout << "ArraySet::operator|(const ArraySet& other) - union operator" << std::endl;
    ArraySet res;
    res = *this;
    for(int i=0;i<other.sz;i++){
        res.insert(other.set[i]);
    }
    return res;
}

ArraySet& ArraySet::operator&=(const ArraySet& other){
    if(setCounter < 10) std::cout << "ArraySet::operator&=(const ArraySet& other) - intersection assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    
    char* res = new char[UNIVERSUM_SIZE+1];
    int resSize = 0;
    bool flag;

    for(int i=0;i<this->sz;i++){
        flag = false;
        for(int j=0;j<other.sz && !flag;j++){
            if(this->set[i]==other.set[j]){
                flag = true;
            }
        }
        if(flag){
            res[resSize] = this->set[i];
            resSize++;
        }
    }
    if(set!=nullptr){
        delete[] set;
    }
    set = res;
    set[resSize] = '\0';
    sz = resSize;
    return *this;
}

ArraySet& ArraySet::operator|=(const ArraySet& other){
    if(setCounter < 10) std::cout << "ArraySet::operator|=(const ArraySet& other) - union assignment operator" << std::endl;
    if(&other==this){
        return *this;
    }
    
    for(int i=0;i<other.sz;i++){
        this->insert(other.set[i]);
    }

    return *this;
}

ArraySet ArraySet::operator~()const{
    if(setCounter < 10) std::cout << "ArraySet::operator~() - complement operator" << std::endl;
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

bool ArraySet::operator==(const ArraySet& other)const{
    if(setCounter < 10) std::cout << "ArraySet::operator==(const ArraySet& other) - equality operator" << std::endl;
    if(this->sz!=other.sz){
        return false;
    }
    bool flag;
    for(int i=0;i<this->sz;i++){
        flag = false;
        for(int j=0;j<other.sz && !flag;j++){
            if(this->set[i]==other.set[j]){
                flag = true;
            }
        }
        if(!flag){
            return false;
        }
    }
    return true;
}

ArraySet ArraySet::subtractSets(const ArraySet& B, const ArraySet& C, const ArraySet& D)const{
    if(setCounter < 10) std::cout << "ArraySet::subtractSets(const ArraySet& B, const ArraySet& C, const ArraySet& D) - subtract sets method" << std::endl;
    ArraySet resSet = *this & ~(B | C | D);
    return resSet;
}

void ArraySet::insert(char ch){
    if(setCounter < 10) std::cout << "ArraySet::insert(char ch) - insert character: " << ch << std::endl;
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

void ArraySet::remove(char ch){
    if(setCounter < 10) std::cout << "ArraySet::remove(char ch) - remove character: " << ch << std::endl;
    if(sz==0){
        return;
    }
    bool flag=false;
    int rmIndex;
    for(int i=0;i<sz&&!flag;i++){
        if(set[i]==ch){
            rmIndex = i;
            flag = true;
        }
    }
    if(!flag){
        return;
    }

    for(int i=rmIndex;i<sz+1;i++){
        set[i] = set[i+1];
    }
    sz--;
}

bool ArraySet::contains(char ch)const{
    if(setCounter < 10) std::cout << "ArraySet::contains(char ch) - check contains character: " << ch << std::endl;
    for(int i=0;i<sz;i++){
        if(set[i]==ch){
            return true;
        }
    }
    return false;
}

void ArraySet::print()const{
    if(setCounter < 10) std::cout << "ArraySet::print() - print set contents" << std::endl;
    for(int i=0;i<sz;i++){
        std::cout << set[i];
        if(i!=sz-1){
            std::cout << ", ";
        }
    }
}

char* ArraySet::toChar()const{
    if(setCounter < 10) std::cout << "ArraySet::toChar() - convert to char array" << std::endl;
    char* res = new char[sz+1];
    strcpy(res, set);
    return res;
}

std::string ArraySet::toString()const{
    if(setCounter < 10) std::cout << "ArraySet::toString() - convert to string" << std::endl;
    std::string res(set);
    return res;
}

std::size_t ArraySet::getSize()const{
    if(setCounter < 10) std::cout << "ArraySet::getSize() - get set size" << std::endl;
    return sz;
}

void ArraySet::clear(){
    if(setCounter < 10) std::cout << "ArraySet::clear() - clear set" << std::endl;
    sz=0;
    set[sz]='\0';
}