#pragma once
#include <vector>
#include <memory>

class Node
{
private:
    int value;
    int index;
    std::vector<Node*> childs;
    std::vector<Node*> parents;
public:
    Node(){
        childs = std::vector<Node*>();
        parents = std::vector<Node*>();
        value=0;
        index=0;
    }
    Node(int _index){
        index = _index;
        value=0;
        childs = std::vector<Node*>();
        parents = std::vector<Node*>();
    }
    Node(int _index, int _value){
        value = _value;
        index = _index;
        childs = std::vector<Node*>();
        parents = std::vector<Node*>();
    }

    void addChild(const std::unique_ptr<Node>& node){
        childs.push_back(node.get());
    }

    void addParent(const std::unique_ptr<Node>& node){
        parents.push_back(node.get());
    }

    bool hasNeighbors(){
        return !childs.empty();
    }

    ~Node(){}
    friend class Graph;
};
