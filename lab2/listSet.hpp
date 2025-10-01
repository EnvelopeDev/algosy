#pragma once
#include <iostream>
#include <cstring>
#include <string>

class ListSet{
private:
    static int setCounter;
    struct Node
    {
        char value;
        Node* next;
        Node(char _value){
            value = _value;
            next = nullptr;
        }
        Node(char _value, Node* _next){
            value = _value;
            next = _next;
        }
    };
    Node* head;
    Node* end;
    static const std::size_t UNIVERSUM_SIZE = 26;
    std::size_t sz;
public:
    ListSet();
    ListSet(const char* inpSet);
    ListSet(const ListSet& other);
    ~ListSet();
    ListSet operator|(const ListSet& other)const;
    ListSet operator&(const ListSet& other)const;
    ListSet& operator=(const ListSet& other);
    ListSet& operator|=(const ListSet& other);
    ListSet& operator&=(const ListSet& other);
    ListSet operator~()const;
    bool operator==(const ListSet& other)const;
    ListSet subtractSets(const ListSet& B, const ListSet& C, const ListSet& D)const;
    std::size_t getSize()const;
    char* toChar()const;
    std::string toString()const;
    void print()const;
    void insert(char ch);
    void remove(char ch);
    bool contains(char ch)const;
    void clear();
};