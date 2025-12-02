#pragma once
#include <vector>
#include <memory>

class Node
{
private:
    int value;
    int index;
    std::vector<std::shared_ptr<Node>> neighbors;
public:
    Node(){
        neighbors = std::vector<std::shared_ptr<Node>>();
        value=0;
        index=0;
    }
    Node(int _index){
        index = _index;
        value=0;
        neighbors = std::vector<std::shared_ptr<Node>>();
    }
    Node(int _value, int _index){
        value = _value;
        index = _index;
        neighbors = std::vector<std::shared_ptr<Node>>();
    }
    Node(int _index, std::vector<std::shared_ptr<Node>> _neighbors) {
        index = _index;
        value=0;
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
