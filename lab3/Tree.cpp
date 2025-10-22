#include "Tree.hpp"

Tree::Tree(){
    root = nullptr;
    numNodes=0;
    maxDepth=0;
    std::random_device rd;
    rng = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0.0, 1.0);
}

Tree::Tree(int _numNodes){
    root = nullptr;
    std::random_device rd;
    rng = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0.0, 1.0);
    makeTreeSimple(_numNodes);
}

Tree::~Tree(){
    clearTree();
}

void Tree::generateRandomTree(){
    if(!isEmpty()){
        clearTree();
    }
    maxTag='a';
    root = makeRandomSubtree(1, 0);
}

Node* Tree::makeRandomSubtree(double chanceOfGeneration, int currDepth){
    Node* node=nullptr;
    if(dist(rng) < chanceOfGeneration){
        node = new Node(maxTag);
        if(maxTag-'a'=='z'-'a' + 1){
            maxTag='a';
        }
        else{
            maxTag++;
        }
        node->left = makeRandomSubtree(chanceOfGeneration-0.15, currDepth+1);
        node->right = makeRandomSubtree(chanceOfGeneration-0.15, currDepth+1);
    }
    if(node){
        if(currDepth>maxDepth){
            maxDepth=currDepth;
        }
        numNodes++;
    }
    return node;
}

int Tree::countNodesOnDeepestLevel()const{
    if(!root){
        return 0;
    }
    std::cout << "Deep bypass: ";
    int numNds = cntNdsDL(root, 0);
    std::cout << '\n';
    return numNds;
}

int Tree::cntNdsDL(Node* node, int depth)const{
    if(!node){
        return 0;
    }
    int count=0;
    std::cout << node->value << '_';
    count += cntNdsDL(node->left, depth + 1);
    if(depth==maxDepth){
        count++;
    }
    count += cntNdsDL(node->right, depth + 1);
    
    return count;
}

void Tree::makeTreeSimple(int _numNodes){
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

void Tree::print(Node* node, std::string prefix, bool isLeft)const{
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