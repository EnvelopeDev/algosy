#pragma once
#include <queue>
#include <iostream>
#include "Node.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <random>
#include <cstring>

class Tree{
private:
    Node* root;
    int maxDepth;
    int numNodes;
    char maxTag;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    void print(Node* node, std::string prefix, bool isLeft)const;
    int cntNdsDL(Node* node, int depth)const;
    Node* makeRandomSubtree(double chanceOfGeneration, int currDepth);
    Node* buildFromArrayDFS(const char* arr, int& index, int maxNodes, int currentDepth, int maxDepth);
public:
    Tree();
    void makeTreeSimple(int _numNodes);
    void generateRandomTree();
    Tree(int _numNodes);
    Tree(const Tree& other);
    ~Tree();
    bool isEmpty()const;
    int countNodesOnDeepestLevel()const;
    void buildTreeFromArray(const char* arr);
    void print()const;
    void clearTree();
    void addNode();
    int getNumNodes()const;
    int getMaxDepth()const;
};