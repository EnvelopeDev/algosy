#include <iostream>
#include "Graph.hpp"

int main(){
	std::vector<std::vector<int>> nodes = {{1,3},{0,2},{1,3},{0,2}};
	Graph gr(nodes);
	std::vector<Graph> forest = gr.createBFSForest();
	for(auto& tree:forest){
		tree.print();
		std::cout << '\n';
	}
	return 0;
}
