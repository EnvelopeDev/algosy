#pragma once
#include "NodeGraph.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <unordered_set>

class Graph
{
private:
    NodeGraph* head;
    int numNodes;
public:
    Graph();
    Graph(std::vector<std::vector<int>> _nodes);
    ~Graph();

    void print();
    int getNumNodes();
};