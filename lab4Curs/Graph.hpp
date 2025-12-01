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
    std::unordered_map<int, std::shared_ptr<Node>> graph;
    int numNodes;
public:
    Graph();
    Graph(std::vector<std::vector<int>> _nodes); //creating graph with the vector of nums of a neighbor-nodes
    ~Graph();

    void print();
    int getNumNodes();
};