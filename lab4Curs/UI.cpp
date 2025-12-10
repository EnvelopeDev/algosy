#include "UI.hpp"

UI::UI(){
    userChoice = -1;
}

void UI::show(){
    do
    {
        std::cout<<"================================[GRAPH CREATOR]================================"<<std::endl;
        std::cout<<"Choose graph option:"<<std::endl;
        std::cout<<std::endl<<"0. Exit"<<std::endl;
        std::cout<<"1. Random graph generation"<<std::endl;
        std::cout<<"2. Custom graph generation"<<std::endl;
        std::cout<<"3. Print graph"<<std::endl;
        std::cout<<"4. Create BFS forest"<<std::endl;
        std::cout<<std::endl<<"Enter your choice: ";
        std::cin>>userChoice;

        system("clear");

        int i = 0;
        std::vector<Graph> forest;

        switch(userChoice){
            case 0:
                std::cout<<"Exiting...."<<std::endl;
                break;
            case 1:
                RandomGeneration();
                std::cout <<std::endl<< "Press Enter to continue..." << std::endl;
                getchar();   
                getchar();   
                break;
            case 2:
                CustomGeneration();
                std::cout <<std::endl<< "Press Enter to continue..." << std::endl;
                getchar();  
                getchar();    
                break;
            case 3:
                std::cout<<"=================================[GRAPH PRINT]================================="<<std::endl;
                graph.printTable();
                std::cout <<std::endl<< "Press Enter to continue..." << std::endl;
                getchar();
                getchar();     
                break;
            case 4:
                system("clear");
                std::cout<<"=================================[BFS  FOREST]================================="<<std::endl;
                forest = graph.createBFSForest();
                for(auto &tree : forest){
                    i++;
                    std::cout<<std::endl<<"Tree No."<< i << std::endl;
                    tree.printTable();
                }
                std::cout <<std::endl<< "Press Enter to continue..." << std::endl;
                getchar();
                getchar();    
                break;
            default:
                std::cout<<"\033[31mWARNING: Wrong choice!\033[0m"<<std::endl;
                std::cout <<std::endl<< "Press Enter to continue..." << std::endl;
                getchar();
                getchar(); 
                break;
        }
        system("clear"); 
    } while (userChoice != 0 );
}

void UI::RandomGeneration(){
    int nodesCount;

    std::cout<<"=================================[RANDOM MODE]================================="<<std::endl;
    std::cout<<"Choose type of generation:\n"<<std::endl;
    std::cout<<"0. Exit"<<std::endl;
    std::cout<<"1. Generation with random nodes count"<<std::endl;
    std::cout<<"2. Generation with custom nodes count\n"<<std::endl;
    std::cout<<"Enter your choice: ";
    std::cin>>userChoice;

    switch (userChoice){
        case 0:
            std::cout<<"Exiting...."<<std::endl;
            return;
        case 1:
            graph.generateRandomGraph(true);
            break;
        case 2:
            std::cout<<"Enter nodes count: ";
            std::cin>>nodesCount;
            graph.generateRandomGraph(false, nodesCount);
            break;
    }
    std::cout<<std::endl<<"Generation successfly!"<<std::endl; 
}

void UI::CustomGeneration(){
    int nodesCount;
    std::vector<std::vector<int>> nodes;

    std::cout<<"=================================[CUSTOM MODE]================================="<<std::endl;
    std::cout<<"Enter nodes count: ";
    std::cin>>nodesCount;
    std::cin.ignore();

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
    
    graph.setGraphWithAdjacencyMatrix(nodes);
    if(!graph.isOrientated()){
        std::cout << "\033[31mWARNING: your graph is not orientated!\033[0m" << std::endl;
    }

    std::cout << "Graph created successfully!" << std::endl;
}

UI::~UI(){}