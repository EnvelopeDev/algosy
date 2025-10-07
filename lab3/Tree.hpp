#pragma once
#include <queue>
#include <iostream>
#include "Node.hpp"
#include <cmath>
#include <stdexcept>

class Tree{
private:
    Node* root;
    int maxDepth;
    int numNodes;
    void print(Node* node)const;
public:
    Tree();
    Tree(int _numNodes);
    Tree(const Tree& other);
    ~Tree();
    Tree& operator=(const Tree& other);
    bool isEmpty()const;
    void print()const;
    int getNumNodes()const;
    int getMaxDepth()const;
};