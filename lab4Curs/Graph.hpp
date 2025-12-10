#pragma once
#include "Node.hpp"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <random>
#include <algorithm>

class Graph
{
private:
    std::unordered_map<int, std::unique_ptr<Node>> graph;
    int numNodes;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    Graph createBFSTree(std::unordered_set<Node*>& passedNodes, Node* startNode);
    std::vector<Node*> getParentlessNodes();
    int randomInt(int min, int max);
    int randomNode(std::unordered_set<int> headNodesIndexes); //generating nodes without head and end nodes
    std::vector<std::vector<int>> generateAdjacencyMatrix();
    std::map<int, std::vector<int>> doAdjacencyMatrix(); //МАТРИЦА СМЕЖНОСТИ
    std::vector<int> generateChilds(std::unordered_set<int> headNodesIndexes, int nodeIndex, std::vector<std::vector<int>>& adjMtx);
    bool isParentless(std::vector<int> mtxAdj, std::unordered_set<int> headNodesIndexes);
    std::vector<int> getPossibleChildNodes(int nodeIndex, std::vector<std::vector<int>>& adjMtx);
public:
    Graph();
    Graph(std::vector<std::vector<int>> _nodes); //creating graph with the vector of nums of a neighbor-nodes
    Graph(const Graph& other);
    ~Graph();

    void generateRandomGraph();
    std::vector<Graph> createBFSForest();
    void printNodes();
    void printTable();
    int getNumNodes();
    void setGraphWithAdjacencyMatrix(std::vector<std::vector<int>> _nodes);
};