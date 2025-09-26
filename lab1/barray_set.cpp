#include "barray_set.hpp"

bool* convStrToBitSet(const char* set){
    bool* res = new bool[POWER_OF_ALPHABET];
    for(int i=0;i<POWER_OF_ALPHABET;i++){
        res[i]=false;
    }

    for(int i=0; i<strlen(set);i++){
        res[set[i]-'A'] = true;
    }
    return res;
}
bool* subtractSets(const bool* A, const bool* B, const bool* C, const bool* D){
    bool* res = new bool[POWER_OF_ALPHABET];
    for(int i=0; i<POWER_OF_ALPHABET;i++){
        res[i] = A[i] && !(B[i] || C[i] || D[i]);
    }
}
char* convBitSetToStr(const bool* set){
    size_t sz=0;

    for(int i=0;i<POWER_OF_ALPHABET;i++){
        if(set[i]){
            sz++;
        }
    }

    char* res = new char[sz+1];
    res[sz] = '\0';

    int resIter=0;
    for(int i=0;i<POWER_OF_ALPHABET && sz;i++){
        if(set[i]){
            res[resIter]='A'+i;
            resIter++;
        }
    }
    return res;
}