#include "Tree.hpp"

int main(){
    Tree tree;
    char userOption;
    int numNodes;
    std::cout << "Generate random tree? (y/n): ";
    std::cin >> userOption;
    if(userOption=='y'){
        tree.generateRandomTree();
    }
    else{
        std::cout << "Enter a number of nodes: ";
        std::cin >> numNodes;
        tree.makeTreeSimple(numNodes);
    }
    std::cout << "\n\n";
    tree.print();
    std::cout << '\n' << "Max depth of the tree: " << tree.getMaxDepth() << "\nNumber of nodes in tree: " << tree.getNumNodes() << '\n';
    int numNodesOnDL = tree.countNodesOnDeepestLevel();
    std::cout << "Number of nodes on the deepest level: " << numNodesOnDL << '\n';
    return 0;
}
