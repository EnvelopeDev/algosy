#include "bmask_set.hpp"

unsigned long long convStrToBitMask(const char* set){
    unsigned long long res = 0ULL;

    for(int i=0; i<strlen(set);i++){
        res = res|(1ULL << (set[i]-'A'));
    }
    
}
unsigned long long subtractBitMaskSets(const unsigned long long A, const unsigned long long B, const unsigned long long C, const unsigned long long D){
    return A & ~(B | C | D);
}
char* convBitMaskToStr(const unsigned long long set){
    size_t sz=0;

    for(int i=0;i<ALPHABET_SIZE;i++){
        if((1ULL<<i) & set){
            sz++;
        }
    }

    char* res = new char[sz+1];
    res[sz] = '\0';

    int resIter=0;
    for(int i=0;i<ALPHABET_SIZE && sz;i++){
        if((1ULL<<i) & set){
            res[resIter]='A'+i;
            resIter++;
        }
    }
    return res;
}