#include "barray_set.hpp"
#include <cstring>

BitArraySet::BitArraySet(const char* elements, int size, char first) 
    : universe_size(size), first_element(first) {
    bits.resize(universe_size, false);
    if (elements != nullptr) {
        size_t length = strlen(elements);
        if (length > 0) {
            for (size_t i = 0; i < length; i++) {
                addElement(elements[i]);
            }
        }
    }
}

// Разность множеств
BitArraySet BitArraySet::subtract(const BitArraySet& other) const {
    BitArraySet result("", universe_size, first_element); // Пустая строка!
    for (int i = 0; i < universe_size; i++) {
        result.bits[i] = this->bits[i] && !other.bits[i];
    }
    return result;
}

// Объединение множеств
BitArraySet BitArraySet::unionWith(const BitArraySet& other) const {
    BitArraySet result("", universe_size, first_element); // Пустая строка!
    for (int i = 0; i < universe_size; i++) {
        result.bits[i] = this->bits[i] || other.bits[i];
    }
    return result;
}

// Добавить элемент
void BitArraySet::addElement(char element) {
    int index = element - first_element;
    if (index >= 0 && index < universe_size) {
        bits[index] = true;
    }
}

// Проверить наличие элемента
bool BitArraySet::contains(char element) const {
    int index = element - first_element;
    if (index >= 0 && index < universe_size) {
        return bits[index];
    }
    return false;
}

// Основная операция: E = A \ (B ∪ C ∪ D)
BitArraySet BitArraySet::subtractSets(const BitArraySet& A, const BitArraySet& B, 
                                    const BitArraySet& C, const BitArraySet& D) {
    BitArraySet unionSet = B.unionWith(C).unionWith(D);
    return A.subtract(unionSet);
}

// Получение всех элементов в виде строки
std::string BitArraySet::toString() const {
    std::string result;
    for (int i = 0; i < universe_size; i++) {
        if (bits[i]) {
            result += first_element + i;
        }
    }
    return result;
}

void BitArraySet::print() const {
    std::cout << toString();
}


int BitArraySet::size() const { 
    return universe_size; 
}

char BitArraySet::first() const { 
    return first_element; 
}