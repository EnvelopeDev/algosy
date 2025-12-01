#pragma once
#include <vector>
#include <memory>

class Node
{
private:
    int value;
    std::vector<std::shared_ptr<Node>> neighbors;
public:
    Node(){
        neighbors = std::vector<std::shared_ptr<Node>>();
        value=0;
    }
    Node(int _value){
        value = _value;
        neighbors = std::vector<std::shared_ptr<Node>>();
    }
    Node(int _value, std::vector<std::shared_ptr<Node>> _neighbors) {
        value = _value;
        neighbors = _neighbors;
    }

    void addNeighbor(const std::shared_ptr<Node>& node){
        neighbors.push_back(node);
    }

    bool hasNeighbors(){
        return !neighbors.empty();
    }

    ~Node(){}
    friend class Graph;
};
