#pragma once
#include "Node.hpp"
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>

class Graph
{
private:
    std::unordered_map<int, std::unique_ptr<Node>> graph;
    int numNodes;
    Graph createBFSTree(std::unordered_set<Node*>& passedNodes, Node* startNode);
    std::vector<Node*> getParentlessNodes();
public:
    Graph();
    Graph(std::vector<std::vector<int>> _nodes); //creating graph with the vector of nums of a neighbor-nodes
    Graph(const Graph& other);
    ~Graph();

    std::vector<Graph> createBFSForest();
    void print();
    int getNumNodes();
};