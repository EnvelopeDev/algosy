#include <iostream>
#include "Graph.hpp"

int main(){
	std::vector<std::vector<int>> nodes = {{1,3},{0,2},{1,3},{0,2}};
	std::vector<std::vector<int>> nodes1 = {{3,2}, {4,5}, {6}, {6}, {6}, {6}, {}};
	Graph gr(nodes1);
	std::vector<Graph> forest = gr.createBFSForest();
	for(auto& tree:forest){
		tree.print();
		std::cout << '\n';
	}
	//gr.print();
	return 0;
}
