#include "Graph.hpp"

Graph::Graph(){
    numNodes=0;
}

Graph::Graph(std::vector<std::vector<int>> _nodes){
    numNodes=_nodes.size();
    if(_nodes.empty()){
        return;
    }

    for(int i=0;i<_nodes.size();i++){
        graph[i] = std::make_shared<Node>(i, i);
    }

    for(size_t i=0;i<_nodes.size();i++){
        for(size_t j=0;j<_nodes[i].size();j++){
            if(i!=_nodes[i][j]){
                graph[i]->addNeighbor(graph[_nodes[i][j]]);
            }
        }
    }
}

Graph::Graph(const Graph& other){
    numNodes = other.numNodes;

    for(int i=0;i<numNodes;i++){
        graph[i] = std::make_shared<Node>(i);
    }

    for(const auto& node:other.graph){
        graph[node.first]->value = node.second->value;
        for(const auto& neighbor:node.second->neighbors){
            graph[node.first]->addNeighbor(graph[neighbor->index]);
        }
    }
}

Graph::~Graph(){}

std::vector<Graph> Graph::createBFSForest(){
    std::vector<Graph> forest;
    std::unordered_set<std::shared_ptr<Node>> passedNodes;

    for(const auto& node:graph){
        if(passedNodes.find(node.second)==passedNodes.end()){
            forest.push_back(createBFSTree(passedNodes, node.second));
        }
    }
    return forest;
}

Graph Graph::createBFSTree(std::unordered_set<std::shared_ptr<Node>>& passedNodes, const std::shared_ptr<Node>& startNode){
    std::queue<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>> nodesNeedToPass;
    Graph tree;
    int currTreeIndex=0;
    tree.graph[currTreeIndex] = std::make_shared<Node>(currTreeIndex, startNode->value);
    nodesNeedToPass.push();
    passedNodes.insert(graph[startNode->index]);
    while(!(nodesNeedToPass.empty())){
        auto curr = nodesNeedToPass.front();
        nodesNeedToPass.pop();
        for(int i=0;i<curr->neighbors.size();i++){
            if(passedNodes.find(curr->neighbors[i]) == passedNodes.end()){
                nodesNeedToPass.push(curr->neighbors[i]);
                passedNodes.insert(curr->neighbors[i]);
            }
        }
    }

    return tree;
}

void Graph::print(){
    if(numNodes==0){
        return;
    }
    std::queue<std::shared_ptr<Node>> nodesNeedToPass;
    std::unordered_set<std::shared_ptr<Node>> passedNodes;

    nodesNeedToPass.push(graph[0]);
    passedNodes.insert(graph[0]);

    while(!(nodesNeedToPass.empty())){
        auto curr = nodesNeedToPass.front();
        std::cout << "Node "<< curr->index << ", value " << curr->value <<": " << '\n';
        for(const auto& node:curr->neighbors){
            std::cout << "  " << node->value << std::endl;
        }
        nodesNeedToPass.pop();
        for(int i=0;i<curr->neighbors.size();i++){
            if(passedNodes.find(curr->neighbors[i]) == passedNodes.end()){
                nodesNeedToPass.push(curr->neighbors[i]);
                passedNodes.insert(curr->neighbors[i]);
            }
        }
    }
}