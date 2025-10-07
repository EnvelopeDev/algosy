#pragma once
class Node
{
private:
    char value;
    Node* right;
    Node* left;
public:
    Node(char _value){
        value = _value;
        right = nullptr;
        left = nullptr;
    }
    ~Node(){
        if(right) delete right;
        if(left) delete left;
    }
    friend class Tree;
};