#include "Graph.hpp"

Graph::Graph(){
    head=nullptr;
    numNodes=0;
}

Graph::Graph(std::vector<std::vector<int>> _nodes){
    numNodes=_nodes.size();
    if(_nodes.empty()){
        head=nullptr;
        return;
    }
    std::vector<NodeGraph*> nodes(_nodes.size(), nullptr);

    for(size_t i=0;i<_nodes.size();i++){
        nodes[i] = new NodeGraph(i+1);
    }

    for(size_t i=0;i<_nodes.size();i++){
        for(size_t j=0;j<_nodes[i].size();j++){
            if(nodes[i]->value!=_nodes[i][j]){
                nodes[i]->addNeighbor(nodes[_nodes[i][j]-1]);
            }
        }
    }
    head = nodes[0];
}

Graph::~Graph(){
    if(head!=nullptr){
        delete head;
    }
}

void Graph::print(){
    if(!head){
        return;
    }
    std::queue<NodeGraph*> nodesNeedToPass;
    std::unordered_set<NodeGraph*> passedNodes;
    NodeGraph* curr;
    nodesNeedToPass.push(head);
    passedNodes.insert(head);
    while(!(nodesNeedToPass.empty())){
        curr = nodesNeedToPass.front();
        std::cout << "Node "<< curr->value << ": "<< '\n';
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