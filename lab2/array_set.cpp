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
