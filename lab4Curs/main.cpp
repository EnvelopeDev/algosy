#include <iostream>
#include "Graph.hpp"

int main(){
	std::vector<std::vector<int>> nodes = {{2,4},{1,3},{2,4},{1,3}};
	Graph gr(nodes);
	gr.print();
	return 0;
}
