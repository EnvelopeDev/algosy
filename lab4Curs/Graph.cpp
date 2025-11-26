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
    std::queue<NodeGraph*> queue;
    std::unordered_set<NodeGraph*> passed;
    NodeGraph* curr;
    queue.push(head);
    passed.insert(head);
    while(!(queue.empty())){
        curr = queue.front();
        std::cout << "Node "<< curr->value << ": "<< '\n';
        for(const auto& node:curr->neighbors){
            std::cout << "  " << node->value << std::endl;
        }
        queue.pop();
        for(int i=0;i<curr->neighbors.size();i++){
            if(passed.find(curr->neighbors[i]) == passed.end()){
                queue.push(curr->neighbors[i]);
                passed.insert(curr->neighbors[i]);
            }
        }
    }
}