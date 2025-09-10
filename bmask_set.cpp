#include "bmask_set.hpp"
#include <cstring>

WordSet::WordSet(const char* elements, int size, char first) 
    : mask(0), universe_size(size), first_element(first) {
    if (elements != nullptr) {
        size_t length = strlen(elements);
        if (length > 0) {
            for (size_t i = 0; i < length; i++) {
                addElement(elements[i]);
            }
        }
    }
}

// Объединение множеств
WordSet WordSet::unionWith(const WordSet& other) const {
    WordSet result("", universe_size, first_element); // Пустая строка!
    result.mask = this->mask | other.mask;
    return result;
}

// Разность множеств
WordSet WordSet::subtract(const WordSet& other) const {
    WordSet result("", universe_size, first_element); // Пустая строка!
    result.mask = this->mask & ~other.mask;
    return result;
}

// Добавить элемент
void WordSet::addElement(char element) {
    int index = element - first_element;
    if (index >= 0 && index < universe_size) {
        mask |= (1ULL << index);
    }
}

// Проверить наличие элемента
bool WordSet::contains(char element) const {
    int index = element - first_element;
    if (index >= 0 && index < universe_size) {
        return (mask & (1ULL << index)) != 0;
    }
    return false;
}

// Основная операция: E = A \ (B ∪ C ∪ D)
WordSet WordSet::subtractSets(const WordSet& A, const WordSet& B, 
                            const WordSet& C, const WordSet& D) {
    WordSet unionSet = B.unionWith(C).unionWith(D);
    return A.subtract(unionSet);
}

// Получение всех элементов в виде строки
std::string WordSet::toString() const {
    std::string result;
    for (int i = 0; i < universe_size; i++) {
        if (mask & (1ULL << i)) {
            result += first_element + i;
        }
    }
    return result;
}

void WordSet::print() const {
    std::cout << toString();
}

int WordSet::size() const { 
    return universe_size; 
}

char WordSet::first() const { 
    return first_element; 
}