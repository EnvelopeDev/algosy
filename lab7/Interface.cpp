#include "Interface.hpp"

Interface::Interface(){}

Interface::~Interface(){}

void Interface::show(){
    std::cout << "МНОЖЕСТВО СОСТОИТ ИЗ ВСЕХ ЗАГЛАВНЫХ ЛАТИНСКИХ БУКВ И СТРОЧНЫХ ДО f ВКЛЮЧИТЕЛЬНО" << std::endl;
    HashTable<std::string, int> ht;
    BitMaskSet bset;
    Generator gen;
    std::string s("HelloWorld");
    ht.insert(s, 60);
    ht.insert("1234", 50);
    ht.insert("HLWD", 40);
    std::cout << ht.getElem("1234")<<std::endl;
    ht.insert("1234", 55);
    std::cout << ht.getElem("1234")<<std::endl;
    std::cout << ht.getElem("HelloWorld")<<std::endl;
    std::cout << ht.getElem("HLWD")<<std::endl;
    ht.printAllValues();
    ht.erase("1234");
    ht.printAllValues();
}