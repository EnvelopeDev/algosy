#include "array_set.hpp"

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
    sz=0;
    set = new char[UNIVERSUM_SIZE+1];
    for(int i=0;i<strlen(inpSet);i++){
        insert(inpSet[i]);
    }
    set[sz]='\0';
}

ArraySet::ArraySet(const ArraySet& other){
    sz=other.sz;
    set = new char[UNIVERSUM_SIZE+1];
    strcpy(set, other.set);
}

ArraySet::~ArraySet(){
    delete[] set;
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
    if(&other==this){
        return *this;
    }
    
    for(int i=0;i<other.sz;i++){
        this->insert(other.set[i]);
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

bool ArraySet::operator==(const ArraySet& other){
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

void ArraySet::remove(char ch){
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

void ArraySet::remove(int removeIndex){
    if(sz==0 || removeIndex >= sz){
        return;
    }

    for(int i=removeIndex;i<sz+1;i++){
        set[i] = set[i+1];
    }
    sz--;
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

void ArraySet::clear(){
    sz=0;
    set[sz]='\0';
}