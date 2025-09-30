#pragma once
#include <iostream>
#include <string>
#include <cstring>

class ListSet{
private:
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
    ListSet operator|(const ListSet& other);
    ListSet operator&(const ListSet& other);
    ListSet& operator=(const ListSet& other);
    ListSet& operator|=(const ListSet& other);
    ListSet& operator&=(const ListSet& other);
    ListSet operator~();
    bool operator==(const ListSet& other);
    std::size_t getSize();
    char* toChar();
    std::string toString();
    void print();
    void insert(char ch);
    void remove(char ch);
    bool constains(char ch);
    void clear();
};