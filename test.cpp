#include "test.hpp"

TestGenerator::TestGenerator(int size, char first) 
    : universe_size(size), first_element(first) {
    std::srand(std::time(0));
}

char* TestGenerator::generateRandomSet(float probability) {
    char* set = new char[universe_size + 1];
    int k = 0;
    
    for (int i = 0; i < universe_size; i++) {
        if (static_cast<float>(std::rand()) / RAND_MAX < probability) {
            set[k++] = first_element + i;
        }
    }
    set[k] = '\0';
    return set;
}

char* TestGenerator::generateSetWithSize(int k) {
    if (k > universe_size) k = universe_size;
    if (k < 0) k = 0;
    
    char* universe = new char[universe_size + 1];
    for (int i = 0; i < universe_size; i++) {
        universe[i] = first_element + i;
    }
    universe[universe_size] = '\0';
    
    for (int i = 0; i < k; i++) {
        int p = std::rand() % (universe_size - i);
        if (p != 0) {
            std::swap(universe[i], universe[i + p]);
        }
    }
    
    universe[k] = '\0';
    return universe;
}

std::vector<char*> TestGenerator::generateAllSubsets() {
    std::vector<char*> subsets;
    int total = 1 << universe_size;
    
    for (int mask = 0; mask < total; mask++) {
        char* subset = new char[universe_size + 1];
        int k = 0;
        
        for (int i = 0; i < universe_size; i++) {
            if (mask & (1 << i)) {
                subset[k++] = first_element + i;
            }
        }
        subset[k] = '\0';
        subsets.push_back(subset);
    }
    
    return subsets;
}

std::vector<char*> TestGenerator::generateGrayCodeSubsets() {
    std::vector<char*> subsets;
    int total = 1 << universe_size;
    
    for (int i = 0; i < total; i++) {
        int gray = i ^ (i >> 1);
        char* subset = new char[universe_size + 1];
        int k = 0;
        
        for (int j = 0; j < universe_size; j++) {
            if (gray & (1 << j)) {
                subset[k++] = first_element + j;
            }
        }
        subset[k] = '\0';
        subsets.push_back(subset);
    }
    
    return subsets;
}

std::vector<char*> TestGenerator::generateAllPermutations() {
    std::vector<char*> permutations;
    
    char* base = new char[universe_size + 1];
    for (int i = 0; i < universe_size; i++) {
        base[i] = first_element + i;
    }
    base[universe_size] = '\0';
    
    generatePermutationsRecursive(base, 0, universe_size - 1, permutations);
    
    delete[] base;
    return permutations;
}

std::vector<char*> TestGenerator::generateRandomPermutations(int count) {
    std::vector<char*> permutations;
    
    char* base = new char[universe_size + 1];
    for (int i = 0; i < universe_size; i++) {
        base[i] = first_element + i;
    }
    base[universe_size] = '\0';
    
    for (int i = 0; i < count; i++) {
        char* perm = new char[universe_size + 1];
        std::strcpy(perm, base);
        
        for (int j = universe_size - 1; j > 0; j--) {
            int k = std::rand() % (j + 1);
            std::swap(perm[j], perm[k]);
        }
        
        permutations.push_back(perm);
    }
    
    delete[] base;
    return permutations;
}

void TestGenerator::generateAllTests(char** A, char** B, char** C, char** D, int numTests) {
    for (int i = 0; i < numTests; i++) {
        A[i] = generateRandomSet(0.7);
        B[i] = generateRandomSet(0.3);
        C[i] = generateRandomSet(0.4);
        D[i] = generateRandomSet(0.2);
    }
}

void TestGenerator::cleanupVector(std::vector<char*>& vec) {
    for (char* item : vec) {
        delete[] item;
    }
    vec.clear();
}

void TestGenerator::cleanupTests(char** arrays, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arrays[i];
    }
}

// Приватная рекурсивная функция
void TestGenerator::generatePermutationsRecursive(char* str, int left, int right, std::vector<char*>& result) {
    if (left == right) {
        char* perm = new char[universe_size + 1];
        std::strcpy(perm, str);
        result.push_back(perm);
    } else {
        for (int i = left; i <= right; i++) {
            std::swap(str[left], str[i]);
            generatePermutationsRecursive(str, left + 1, right, result);
            std::swap(str[left], str[i]);
        }
    }
}