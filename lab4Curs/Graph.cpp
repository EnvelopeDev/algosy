#include "Graph.hpp"

Graph::Graph(){
    std::random_device rd;
    rng = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0.0, 1.0);
    numNodes=0;
}

Graph::Graph(std::vector<std::vector<int>> _nodes){
    numNodes=_nodes.size();
    std::random_device rd;
    rng = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0.0, 1.0);
    if(_nodes.empty()){
        return;
    }

    for(size_t i=0;i<_nodes.size();i++){
        graph[i] = std::make_unique<Node>(i, i);
    }

    for(size_t i=0;i<_nodes.size();i++){
        for(size_t j=0;j<_nodes[i].size();j++){
            if(i!=_nodes[i][j]){
                graph[i]->addChild(graph[_nodes[i][j]]);
                graph[_nodes[i][j]]->addParent(graph[i]);
            }
        }
    }
}

Graph::Graph(const Graph& other){
    numNodes = other.numNodes;
    std::random_device rd;
    rng = std::mt19937(rd());
    dist = std::uniform_real_distribution<double>(0.0, 1.0);

    for(const auto& node:other.graph){
        graph[node.first] = std::make_unique<Node>(node.first);
    }

    for(const auto& node:other.graph){
        graph[node.first]->value = node.second->value;
        for(const auto& neighbor:node.second->childs){
            graph[node.first]->addChild(graph[neighbor->index]);
        }

        for(const auto& parent:node.second->parents){
            graph[node.first]->addParent(graph[parent->index]);
        }
    }
}

Graph::~Graph(){}

void Graph::setGraphWithAdjacencyMatrix(std::vector<std::vector<int>> _nodes){
    graph.clear();
    for(size_t i=0;i<_nodes.size();i++){
        graph[i] = std::make_unique<Node>(i, i);
    }

    for(size_t i=0;i<_nodes.size();i++){
        for(size_t j=0;j<_nodes[i].size();j++){
            if(i!=_nodes[i][j]){
                graph[i]->addChild(graph[_nodes[i][j]]);
                graph[_nodes[i][j]]->addParent(graph[i]);
            }
        }
    }
}

std::vector<int> Graph::getPossibleChildNodes(int nodeIndex, std::vector<std::vector<int>>& adjMtx, std::unordered_set<int> headNodesIndexes){
    std::vector<int> possibleChilds;
    for(int i=0;i<adjMtx.size();i++){
        if(nodeIndex==i || headNodesIndexes.find(i) != headNodesIndexes.end()){
            continue;
        }

        if(std::find(adjMtx[i].begin(), adjMtx[i].end(), nodeIndex) == adjMtx[i].end()){
            possibleChilds.push_back(i);
        }
    }
    return possibleChilds;
}

std::vector<int> Graph::generateChilds(int nodeIndex, std::vector<std::vector<int>>& adjMtx, std::unordered_set<int> headNodesIndexes, bool isHeadNode, std::vector<int> nodePool){
    int numChilds;
    double chance = dist(rng);

    if(chance<0.2 && !isHeadNode){
        return {};
    }

    if(numNodes<8){
        numChilds=randomInt(1, 3);
    }
    else{
        numChilds=randomInt(2, 4);
    }

    std::vector<int> childs;
    std::vector<int> possibleChilds = getPossibleChildNodes(nodeIndex, adjMtx, headNodesIndexes);
    if(possibleChilds.empty()){
        return {};
    }

    if(possibleChilds.size() < numChilds){
        return possibleChilds;
    }

    int randNodeIndex;
    while(childs.size() < numChilds){
        randNodeIndex = randomInt(0, possibleChilds.size()-1);

        if(std::find(childs.begin(), childs.end(), possibleChilds[randNodeIndex])==childs.end()){
            childs.push_back(possibleChilds[randNodeIndex]);
        }
    }

    return childs;
}

std::vector<std::vector<int>> Graph::generateAdjacencyMatrix(){
    int numHeadNodes = randomInt(1, numNodes/4);
    std::unordered_set<int> headNodesIndexes;
    int headIndex;

    while(headNodesIndexes.size() < numHeadNodes){
        headIndex = randomInt(0, numNodes-1);
        if(headNodesIndexes.find(headIndex)==headNodesIndexes.end()){
            headNodesIndexes.insert(headIndex);
        }
    }

    std::vector<std::vector<int>> mtx(numNodes);
    for(int i=0;i<numNodes;i++){
        mtx[i]={};
    }
    int numChilds;
    for(int i=0;i<numNodes;i++){
        if(headNodesIndexes.find(i)!=headNodesIndexes.end()){
            continue;
        }
        std::vector<int> possibleChilds;
        for(int j=0;j<numNodes;j++){
            if(i==j){
                continue;
            }
        }
        mtx[i] = generateChilds(i, mtx, headNodesIndexes);
    }

    for(const auto& node:headNodesIndexes){
        mtx[node] = generateChilds(node, mtx, headNodesIndexes, true);
    }
    return mtx;
}

void Graph::generateRandomGraph(){
    double chance = dist(rng);
    graph.clear();
    if(chance < 0.10){
        numNodes = randomInt(4, 6);
    }
    else if(chance < 0.9){
        numNodes = randomInt(7, 20);
    }
    else{
        numNodes = randomInt(20, 30);
    }
    
    setGraphWithAdjacencyMatrix(generateAdjacencyMatrix());
}

std::vector<Node*> Graph::getParentlessNodes(){
    std::vector<Node*> parentlessNodes;
    for(const auto& node:graph){
        if(node.second->parents.empty()){
            parentlessNodes.push_back(node.second.get());
        }
    }
    return parentlessNodes;
}

std::vector<Graph> Graph::createBFSForest(){
    std::vector<Graph> forest;
    std::unordered_set<Node*> passedNodes;
    std::vector<Node*> startNodes = getParentlessNodes();
    if(startNodes.empty()){
        startNodes.push_back((*graph.begin()).second.get());
    }

    for(const auto& node:startNodes){
        if(passedNodes.find(node)==passedNodes.end()){
            forest.push_back(createBFSTree(passedNodes, node));
        }
    }
    return forest;
}

Graph Graph::createBFSTree(std::unordered_set<Node*>& passedNodes, Node* startNode){
    std::queue<Node*> nodesNeedToPass;
    Graph tree;
    tree.graph[startNode->index] = std::make_unique<Node>(startNode->index, startNode->value);
    tree.numNodes=1;
    nodesNeedToPass.push(startNode);
    passedNodes.insert(startNode);

    while(!(nodesNeedToPass.empty())){
        Node* curr = nodesNeedToPass.front();
        nodesNeedToPass.pop();
        for(int i=0;i<curr->childs.size();i++){
            if(passedNodes.find(curr->childs[i]) == passedNodes.end()){
                nodesNeedToPass.push(curr->childs[i]);
                passedNodes.insert(curr->childs[i]);
                tree.graph[curr->childs[i]->index] = std::make_unique<Node>(curr->childs[i]->index, curr->childs[i]->value);
                tree.graph[curr->index]->addChild(tree.graph[curr->childs[i]->index]);
                tree.graph[curr->childs[i]->index]->addParent(tree.graph[curr->index]);
                tree.numNodes++;
            }
        }
    }

    return tree;
}

std::map<int, std::vector<int>> Graph::doAdjacencyMatrix(){
    std::map<int, std::vector<int>> adjacencyMatrix;

    for(const auto& node:graph){
        adjacencyMatrix[node.first].resize(node.second->childs.size());
        for(int i=0;i<node.second->childs.size();i++){
            adjacencyMatrix[node.first][i] = node.second->childs[i]->index;
        }
    }
    return adjacencyMatrix;
}

void Graph::printTable(){
    if(numNodes == 0){
        std::cout << "Graph is empty" << std::endl;
        return;
    }
    std::cout << std::endl << "ADJACENCY MATRIX" << std::endl;
    std::cout << "(direction: from column to row)" << std::endl << std::endl;
    std::map<int, std::vector<int>> adjacencyMatrix = doAdjacencyMatrix();
    std::vector<int> nodeIndexes(numNodes);
    int currIndex=0;

    std::cout << "    |";
    for(const auto& node:adjacencyMatrix){
        if(node.first < 10){
            std::cout << "  " << node.first << " |";
        }
        else{
            std::cout << " " << node.first << " |";
        }
        nodeIndexes[currIndex] = node.first;
        currIndex++;
    }
    std::cout << std::endl;
    for(int i = 0; i < numNodes + 1; i++){
        std::cout << "-----";
    }
    std::cout << std::endl;
    
    for(int row=0; row<numNodes; row++){
        if(nodeIndexes[row] < 10){
            std::cout << "  " << nodeIndexes[row] << " |";
        }
        else{
            std::cout << " " << nodeIndexes[row] << " |";
        }

        for(int col=0; col<numNodes; col++){
            bool hasEdge = false;
            auto it = adjacencyMatrix.find(nodeIndexes[col]);
            if(it != adjacencyMatrix.end()){
                for(int childIndex : it->second){
                    if(childIndex == nodeIndexes[row]){
                        hasEdge = true;
                        break;
                    }
                }
            }

            if(hasEdge){
                std::cout << "  1 |";
            }
            else{
                std::cout << "  0 |";
            }
        }
        std::cout << std::endl;
    }
}

void Graph::printNodes(){
    if(numNodes==0){
        std::cout << "Graph is empty" << std::endl;
        return;
    }
    std::queue<Node*> nodesNeedToPass;
    std::unordered_set<Node*> passedNodes;
    for(const auto& node:graph){
        if(passedNodes.find(node.second.get()) == passedNodes.end()){
            nodesNeedToPass.push(node.second.get());
            passedNodes.insert(node.second.get());
            while(!(nodesNeedToPass.empty())){
                Node* curr = nodesNeedToPass.front();
                std::cout << "Node "<< curr->index << ", value " << curr->value <<": " << '\n';
                for(const auto& node:curr->childs){
                    std::cout << "  " << node->value << std::endl;
                }
                nodesNeedToPass.pop();
                for(int i=0;i<curr->childs.size();i++){
                    if(passedNodes.find(curr->childs[i]) == passedNodes.end()){
                        nodesNeedToPass.push(curr->childs[i]);
                        passedNodes.insert(curr->childs[i]);
                    }
                }
            }
        }
    }
}

int Graph::randomInt(int min, int max){
    return (rng()%(max+1-min))+min;
}

int Graph::randomNode(std::unordered_set<int> headNodesIndexes){
    int randNodeIndex;

    do{
        randNodeIndex = randomInt(0, numNodes-1);
    }while(headNodesIndexes.find(randNodeIndex) != headNodesIndexes.end());

    return randNodeIndex;
}