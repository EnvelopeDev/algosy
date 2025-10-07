#include "Tree.hpp"

std::random_device rd;
std::mt19937 rng(rd());

Tree::Tree(){
    root = nullptr;
    numNodes=0;
    maxDepth=0;
}

Tree::Tree(int _numNodes){
    root = nullptr;
    makeTree(_numNodes);
}

Tree::~Tree(){
    clearTree();
}

void Tree::generateRandomTree(){
    generateNumNodes();
    makeTree(numNodes);
}

void Tree::generateNumNodes(){
    int distribution = rng()%100;
    
    if(distribution<50){
        numNodes = 5 + (rng()%6);
    }else if(distribution<95){
        numNodes = 11 + (rng()%10);
    }else{
        numNodes = 26 + (rng()%25);
    }
}

Tree& Tree::operator=(const Tree& other){
    if(this==&other){
        return *this;
    }
    this->makeTree(other.numNodes);
    return *this;
}

int Tree::countNodesInDeepestLevel()const{
    if(!root){
        return 0;
    }
    return cntNdsDL(root, 0);
}

int Tree::cntNdsDL(Node* node, int depth)const{
    if(!node){
        return 0;
    }
    int count=0;
    
    count += cntNdsDL(node->left, depth + 1);
    if(depth==maxDepth){
        count++;
    }
    count += cntNdsDL(node->right, depth + 1);
    
    return count;
}

void Tree::makeTree(int _numNodes){
    if(!isEmpty()){
        clearTree();
    }
    numNodes = _numNodes;
    if(numNodes<0){
        throw std::invalid_argument("Binary tree can`t be initialized with a negative number of the nodes!");
    }
    
    if(numNodes==0){
        root=nullptr;
        maxDepth=0;
        return;
    }
    maxDepth = log2(numNodes);
    root = new Node('a');
    std::queue<Node*> freeNodes;
    freeNodes.push(root);
    Node* curr;
    for(int i=1;i<numNodes;i++){
        curr = freeNodes.front();
        if(!curr->left){
            curr->left = new Node('a'+(i%26));
            freeNodes.push(curr->left);
        }else{
            curr->right = new Node('a'+(i%26));
            freeNodes.push(curr->right);
            freeNodes.pop();
        }
    }
}

void Tree::clearTree(){
    delete root;
    maxDepth=0;
    numNodes=0;
}

void Tree::print()const{
    if(!root){
        return;
    }
    std::cout << root->value << '\n';
    if(root->left || root->right){
        print(root->left, "", true);
        print(root->right, "", false);
    }
}

void Tree::print(Node* node, std::string prefix, bool isLeft) const {
    if(!node){
        return;
    }

    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << node->value << '\n';
    
    if(node->left || node->right){
        std::string newPrefix = prefix + (isLeft ? "│   " : "    ");
        print(node->left, newPrefix, true);
        print(node->right, newPrefix, false);
    }
}

bool Tree::isEmpty()const{
    return !root;
}

int Tree::getNumNodes()const{return numNodes;}
int Tree::getMaxDepth()const{return maxDepth;}