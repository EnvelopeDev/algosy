#pragma once
#include <vector>
class NodeGraph
{
private:
    int value;
    std::vector<NodeGraph*> neighbors;
public:
    NodeGraph(){
        neighbors = std::vector<NodeGraph*>();
        value=0;
    }
    NodeGraph(int _value){
        value = _value;
        neighbors = std::vector<NodeGraph*>();
    }
    NodeGraph(int _value, std::vector<NodeGraph*> _neighbors) {
        value = _value;
        neighbors = _neighbors;
    }

    void addNeighbor(NodeGraph* node){
        neighbors.push_back(node);
    }

    bool hasNeighbors(){
        return !neighbors.empty();
    }

    ~NodeGraph(){}
    friend class Graph;
};
