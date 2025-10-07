#pragma once
#include <queue>
#include <iostream>
#include "Node.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <random>

class Tree{
private:
    Node* root;
    int maxDepth;
    int numNodes;
    void print(Node* node, std::string prefix, bool isLeft)const;
    void makeTree(int _numNodes);
    void generateNumNodes();
public:
    Tree();
    void generateRandomTree();
    Tree(int _numNodes);
    Tree(const Tree& other);
    ~Tree();
    Tree& operator=(const Tree& other);
    bool isEmpty()const;
    void print()const;
    void clearTree();
    int getNumNodes()const;
    int getMaxDepth()const;
};