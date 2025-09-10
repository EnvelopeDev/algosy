#include <iostream>
#include <vector>
#include "array_set.hpp"
#include "barray_set.hpp"
#include "bmask_set.hpp"
#include "list.hpp"
#include "test.hpp"
#include <windows.h>

char* substrSets(const char* A, const char* B, const char* C, const char* D);

void testAllSubsets() {
    std::cout << "\n=== ГЕНЕРАЦИЯ ВСЕХ ПОДМНОЖЕСТВ ===\n\n";
    
    TestGenerator generator(4, 'A');
    std::vector<char*> subsets = generator.generateAllSubsets();
    
    std::cout << "Все подмножества универсума {A,B,C,D} (2^4 = " << subsets.size() << "):\n";
    for (size_t i = 0; i < subsets.size(); i++) {
        std::cout << i + 1 << ": {" << (subsets[i][0] ? subsets[i] : "пусто") << "}\n";
    }
    
    TestGenerator::cleanupVector(subsets);
}

void testGrayCodeSubsets() {
    std::cout << "\n=== КОД ГРЕЯ ===\n\n";
    
    TestGenerator generator(3, 'A');
    std::vector<char*> graySubsets = generator.generateGrayCodeSubsets();
    
    std::cout << "Подмножества в порядке кода Грея {A,B,C}:\n";
    for (size_t i = 0; i < graySubsets.size(); i++) {
        std::cout << i + 1 << ": {" << (graySubsets[i][0] ? graySubsets[i] : "пусто") << "}\n";
        if (i > 0) {
            // Проверяем, что соседние отличаются на 1 элемент
            int diff = 0;
            for (int j = 0; j < 3; j++) {
                bool in_prev = (strchr(graySubsets[i-1], 'A' + j) != nullptr);
                bool in_curr = (strchr(graySubsets[i], 'A' + j) != nullptr);
                if (in_prev != in_curr) diff++;
            }
            std::cout << "   (отличается на " << diff << " элемента)\n";
        }
    }
    
    TestGenerator::cleanupVector(graySubsets);
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
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // Основные тесты операций
    testBasicOperations();
    
    // Тесты подмножеств и перестановок
    testAllSubsets();
    testGrayCodeSubsets();
    testPermutations();
    testRandomPermutations();
    
    return 0;
}