#include <iostream>
#include <vector>
#include "array_set.hpp"
/*#include "barray_set.hpp"
#include "bmask_set.hpp"*/
#include "list.hpp"
//#include "test.hpp"

//char* substrSets(const char* A, const char* B, const char* C, const char* D);

/*void testAllSubsets() {
    std::cout << "\n=== ГЕНЕРАЦИЯ ВСЕХ ПОДМНОЖЕСТВ ===\n\n";
    
    TestGenerator generator(4, 'A');
    std::vector<char*> subsets = generator.generateAllSubsets();
    
    std::cout << "Все подмножества универсума {A,B,C,D} (2^4 = " << subsets.size() << "):\n";
    for (size_t i = 0; i < subsets.size(); i++) {
        std::cout << i + 1 << ": {" << (subsets[i][0] ? subsets[i] : "пусто") << "}\n";
    }
    
    TestGenerator::cleanupVector(subsets);
}


void testPermutations() {
    std::cout << "\n=== ВСЕ ПЕРЕСТАНОВКИ ===\n\n";
    
    TestGenerator generator(3, 'A');
    std::vector<char*> permutations = generator.generateAllPermutations();
    
    std::cout << "Все перестановки {A,B,C} (3! = " << permutations.size() << "):\n";
    for (size_t i = 0; i < permutations.size(); i++) {
        std::cout << i + 1 << ": " << permutations[i] << "\n";
    }
    
    TestGenerator::cleanupVector(permutations);
}

void testRandomPermutations() {
    std::cout << "\n=== СЛУЧАЙНЫЕ ПЕРЕСТАНОВКИ ===\n\n";
    
    TestGenerator generator(5, 'A');
    std::vector<char*> randomPerms = generator.generateRandomPermutations(5);
    
    std::cout << "5 случайных перестановок {A,B,C,D,E}:\n";
    for (size_t i = 0; i < randomPerms.size(); i++) {
        std::cout << i + 1 << ": " << randomPerms[i] << "\n";
    }
    
    TestGenerator::cleanupVector(randomPerms);
}

void testBasicOperations() {
    std::cout << "=== ОСНОВНЫЕ ТЕСТЫ ОПЕРАЦИЙ ===\n\n";
    
    const int NUM_TESTS = 2;
    const int UNIVERSE_SIZE = 5;
    
    TestGenerator generator(UNIVERSE_SIZE, 'A');
    
    char* A[NUM_TESTS];
    char* B[NUM_TESTS];
    char* C[NUM_TESTS];
    char* D[NUM_TESTS];
    
    generator.generateAllTests(A, B, C, D, NUM_TESTS);
    
    for (int test = 0; test < NUM_TESTS; test++) {
        std::cout << "ТЕСТ " << test + 1 << ":\n";
        std::cout << "A: " << A[test] << "\n";
        std::cout << "B: " << B[test] << "\n";
        std::cout << "C: " << C[test] << "\n";
        std::cout << "D: " << D[test] << "\n\n";
        
        char* result1 = substrSets(A[test], B[test], C[test], D[test]);
        std::cout << "Результат: " << result1 << "\n\n";
        delete[] result1;
    }
    
    TestGenerator::cleanupTests(A, NUM_TESTS);
    TestGenerator::cleanupTests(B, NUM_TESTS);
    TestGenerator::cleanupTests(C, NUM_TESTS);
    TestGenerator::cleanupTests(D, NUM_TESTS);
}*/

int main() {
    std::cout << "_____ARRAY SET_____\n";
    char A[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0'}; //B E G H
    char B[] = {'C', 'D', '\0'};
    char C[] = {'A', 'F', '\0'};
    char D[] = {'I', 'J', '\0'};
    char* E = substrSets(A, B, C, D);
    for(int i=0; i<strlen(E);i++){
        std::cout << E[i]<< ' ';
    }
    std::cout <<'\n';
    std::cout << "_____LIST SET_____\n";
    List<char> setA;
    List<char>* setB = new List<char>("DP", 2);
    List<char>* setC = new List<char>("AF", 2);
    List<char>* setD = new List<char>("GU", 2);
    List<char>* setRes;
    for(int i='A';i<'K';i++){
        setA.push_back(i);
    }
    
    List<char>* lists[3] = {setB, setC, setD};
    setRes = setA.substractLists(lists, 3);
    setRes->print();
    return 0;
}