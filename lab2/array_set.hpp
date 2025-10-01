#pragma once
#include <iostream>
#include <cstring>
#include <string>

class ArraySet{
private:
    char* set; //set in the form of an array of characters
    static const std::size_t UNIVERSUM_SIZE = 26; //size of latin alphabet
    static int setCounter;
    std::size_t sz; //number of elements in the set (size)
public:
    ArraySet(); //default constructor
    ArraySet(const char* inpSet); //constructor with the array of characters
    ArraySet(const ArraySet& other); //copy constructor
    ~ArraySet(); //destructor
    ArraySet operator|(const ArraySet& other)const; //union operator
    ArraySet operator&(const ArraySet& other)const; //intersection operator
    ArraySet& operator=(const ArraySet& other); //assignment operator
    ArraySet& operator|=(const ArraySet& other); //union operator with assignmenet
    ArraySet& operator&=(const ArraySet& other); //intersection operator with assignmenet
    ArraySet operator~()const; //inverse operator
    bool operator==(const ArraySet& other)const; //operator to compare sets
    ArraySet subtractSets(const ArraySet& B, const ArraySet& C, const ArraySet& D)const; //operation of the subtraction (E = A \ (B ∪ C ∪ D))
    std::size_t getSize()const;
    char* toChar()const; //converting ArraySet object to the character array
    std::string toString()const; //converting ArraySet object to the stl string
    void print()const;
    void insert(char ch); //adding character to the set
    void remove(char ch); //removing character from the set
    bool contains(char ch)const; //checking if the set contains the character
    void clear(); //clearing set, removing all the elements
};