#include "UI.hpp"


UI::UI(){
    GraphCreator();
}

void UI::GraphCreator(){
    int graphCreationMode;

    std::cout<<"================================[GRAPH CREATOR]================================"<<std::endl;
    std::cout<<"Choose graph creation mode:\n"<<std::endl;
    std::cout<<"0. Exit"<<std::endl;
    std::cout<<"1. Random generation"<<std::endl;
    std::cout<<"2. Custom generation\n"<<std::endl;
    std::cout<<"Enter your choice: ";
    std::cin>>graphCreationMode;

    system("cls");//НА ЛИНУКСЕ ПОМЕНЯТЬ НА clear!!!!!!!!

    switch(graphCreationMode){
        case 0:
            std::cout<<"Exiting...."<<std::endl;
            return;
        case 1:
            RandomGeneration();
            break;
        case 2:
            CustomGeneration();
            break;
    }

    system("cls");//НА ЛИНУКСЕ ПОМЕНЯТЬ НА clear!!!!!!!!
    graph.printTable();
}

void UI::RandomGeneration(){
    int typeOfGeneration;
    int nodesCount;

    std::cout<<"===============================[RANDOM MODE]==============================="<<std::endl;
    std::cout<<"Choose type of generation:\n"<<std::endl;
    std::cout<<"0. Exit"<<std::endl;
    std::cout<<"1. Generation with random nodes count"<<std::endl;
    std::cout<<"2. Generation with custom nodes count\n"<<std::endl;
    std::cout<<"Enter your choice: ";
    std::cin>>typeOfGeneration;

    switch (typeOfGeneration){
        case 0:
            std::cout<<"Exiting...."<<std::endl;
            return;
        case 1:
            graph.generateRandomGraph(true);
            std::cout<<"Generation successfly!"<<std::endl;
            break;
        case 2:
            std::cout<<"Enter nodes count: ";
            std::cin>>nodesCount;
            std::cout<<"";
            graph.generateRandomGraph(false, nodesCount);
            std::cout<<"Generation successfly!"<<std::endl;          
            break;
    }
}

void UI::CustomGeneration(){
    int nodesCount;
    std::vector<std::vector<int>> nodes;

    std::cout<<"===============================[CUSTOM MODE]==============================="<<std::endl;
    std::cout<<"Enter nodes count: ";
    std::cin>>nodesCount;
    std::cin.ignore();

    //nodes.resize(nodesCount);
    std::string childs_str;
    std::unordered_set<int> childsIndex;
    for(int i = 0; i < nodesCount; i++){
        std::vector<int> childs;
        childsIndex.clear();
        std::cout<<"Enter node "<< i << " childs (Maximum "<<nodesCount - 1<<"): ";
        std::getline(std::cin, childs_str);

        std::stringstream ss(childs_str);
        int nodeIndex;

        while(ss >> nodeIndex){
            if(nodeIndex >= 0 && nodeIndex < nodesCount && nodeIndex != i){
                childsIndex.insert(nodeIndex);
            }
        }
        for(const auto &node : childsIndex){
            childs.push_back(node);
            
        }
        nodes.push_back(childs);
    }
    for(const auto &childs : nodes){
        for(const auto &node : childs){
            std::cout<<node<<" ";
        }
        std::cout<<std::endl;
        
    }
    
    graph.setGraphWithAdjacencyMatrix(nodes);
    graph.printTable();
    std::cin>>nodesCount;

    std::cout << "Graph created successfully!" << std::endl;
}

UI::~UI(){}