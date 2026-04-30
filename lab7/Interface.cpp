#include "Interface.hpp"

Interface::Interface(){}

Interface::~Interface(){}

void Interface::show(){
    std::cout << "МНОЖЕСТВО СОСТОИТ ИЗ ВСЕХ ЗАГЛАВНЫХ ЛАТИНСКИХ БУКВ И СТРОЧНЫХ ДО f ВКЛЮЧИТЕЛЬНО" << std::endl;
    HashTable<std::string, BitMaskSet> ht;
    BitMaskSet bset;
    Generator gen;
    std::string s("HelloWorld");
    for(int i=0;i<10;i++){
        bset.setMask(gen.generateSet(4, 32));
        ht.insert(s, bset);
        s[0]++;
    }
}