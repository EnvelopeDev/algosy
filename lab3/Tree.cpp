#include "Tree.hpp"

Tree::Tree(){
    root = nullptr;
    numNodes=0;
    maxDepth=0;
}

Tree::Tree(int _numNodes){
    numNodes = _numNodes;
    if(numNodes<0){
        throw std::invalid_argument("Binary tree can`t be initialized with a negative number of the nodes!");
    }
    
    if(numNodes==1){
        maxDepth=0;
    }
    else{
        maxDepth = sqrt(numNodes);
    }

    if(numNodes==0){
        root=nullptr;
        return;
    }

    root = new Node('a');
    std::queue<Node*> freeNodes;
    freeNodes.push(root);
    Node* curr;
    for(int i=1;i<numNodes;i++){
        curr = freeNodes.front();
        if(curr->left==nullptr){
            curr->left = new Node('a'+i);
            freeNodes.push(curr->left);
        }else{
            curr->right = new Node('a'+i);
            freeNodes.push(curr->right);
            freeNodes.pop();
        }
    }
}

Tree::~Tree(){
    delete root;
}

void Tree::print()const{
    if(isEmpty()){
        return;
    }
    if(maxDepth==0){
        std::cout << root->value << '\n';
        return;
    }

    std::queue<Node*> nodes;
    std::cout << root->value << '\n';
    nodes.push(root->left);
    if(root->right){
        nodes.push(root->right);
    }
    for(int i=0;i<maxDepth;i++){

    }
}

void Tree::print(Node* node)const{
    if(node==nullptr){
        return;
    }
    std::cout << node->value << " ";
    print(node->left);
    print(node->right);
}

bool Tree::isEmpty()const{
    return root == nullptr;
}

int Tree::getNumNodes()const{return numNodes;}
int Tree::getMaxDepth()const{return maxDepth;}