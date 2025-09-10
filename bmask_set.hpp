#pragma once
#include <iostream>
#include <string>

class WordSet {
private:
    unsigned long long mask;
    int universe_size;
    char first_element;
    
public:
    
    WordSet(const char* elements, int size, char first);
    // Методы
    void addElement(char element);
    bool contains(char element) const;
    WordSet unionWith(const WordSet& other) const;
    WordSet subtract(const WordSet& other) const;
    std::string toString() const;
    void print() const;
    
    // Статический метод для основной операции
    static WordSet subtractSets(const WordSet& A, const WordSet& B, 
                              const WordSet& C, const WordSet& D);
    
    // Геттеры
    int size() const;
    char first() const;
};