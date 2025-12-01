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
        graph[i] = std::make_unique<Node>(i+1);
    }

    for(size_t i=0;i<_nodes.size();i++){
        for(size_t j=0;j<_nodes[i].size();j++){
            if(i!=_nodes[i][j]-1){
                graph[i]->addNeighbor(graph[_nodes[i][j]-1]);
            }
        }
    }
}

Graph::~Graph(){}

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