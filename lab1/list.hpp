#pragma once
#include <iostream>
#include <stdexcept> //for calling exceptions

struct Node
{
    char value;
    Node* next;
};

void push_back(Node** head, char value);
void print(Node* head);
Node* substructSetList(Node* A, Node* B, Node* C, Node* D);
int listSize(Node* head);
char* toChar(Node* head);