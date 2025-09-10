#include "array_set.hpp"
#include <iostream>
#include <cstring>

char* substrSets(const char* A, const char* B, const char* C, const char* D) {
    char* res = new char[strlen(A)];
    int resK = 0;
    bool flag = true;
    
    for (int i = 0; i < strlen(A); i++) {
        for(int j = 0; j < strlen(B) && flag; j++) {
            if(A[i] == B[j]) {
                flag = false;
            }
        }
        for(int j = 0; j < strlen(C) && flag; j++) {
            if(A[i] == C[j]) {
                flag = false;
            }
        }
        for(int j = 0; j < strlen(D) && flag; j++) {
            if(A[i] == D[j]) {
                flag = false;
            }
        }

        if(flag) {
            res[resK] = A[i];
            resK++;
        }
        flag = true;
    }
    
    res[resK] = '\0';
    return res;
}
