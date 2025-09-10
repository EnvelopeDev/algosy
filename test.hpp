#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

class TestGenerator {
private:
    int universe_size;
    char first_element;
    
    // Рекурсивная функция для генерации перестановок
    void generatePermutationsRecursive(char* str, int left, int right, std::vector<char*>& result);
    
public:
    TestGenerator(int size = 10, char first = 'A');
    
    // Основные методы генерации
    char* generateRandomSet(float probability = 0.5);
    char* generateSetWithSize(int k);
    void generateAllTests(char** A, char** B, char** C, char** D, int numTests = 5);
    
    // Методы для подмножеств и перестановок
    std::vector<char*> generateAllSubsets();
    std::vector<char*> generateGrayCodeSubsets();
    std::vector<char*> generateAllPermutations();
    std::vector<char*> generateRandomPermutations(int count);
    
    // Методы очистки
    static void cleanupVector(std::vector<char*>& vec);
    static void cleanupTests(char** arrays, int size);
};