#pragma once
#include <queue>
#include <iostream>
#include "Node.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <cstring>
#include <random>

class Tree{
private:
    Node* root;
    Node* makeRandomSubtree(double chanceOfGeneration, int currDepth);
    Node* buildFromArrayDFS(const char* arr, int& index, int maxNodes, int currentDepth, int maxDepth);
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    char maxTag;
    void print(Node* node, std::string prefix, bool isLeft)const;
    int maxDepth;
    int numNodes;
    int getRealMaxDepth(Node* node, int depth)const;
    int cntNdsDL(Node* node, int depth, int targetDepth)const;
public:
    Tree();
    ~Tree();
    Tree(int _numNodes);
    Tree(const Tree& other);
    bool isEmpty()const;
    int getNumNodes()const;
    int getMaxDepth()const;
    int countNodesOnDeepestLevel()const;
    void makeTreeSimple(int _numNodes);
    void buildTreeFromArray(const char* arr);
    void generateRandomTree();
    void print()const;
    void clearTree();
    void addNode();
};
