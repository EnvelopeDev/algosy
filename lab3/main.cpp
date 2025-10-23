#include "Tree.hpp"

int main(){
        Tree tree;
    char userOption;

    std::cout << "Choose tree creation method:\n";
    std::cout << "1 - Random tree\n";
    std::cout << "2 - Simple tree\n";
    std::cout << "3 - From array\n";
    std::cout << "Your choice: ";
    std::cin >> userOption;

    if(userOption == '1'){
        tree.generateRandomTree();
    }
    else if(userOption == '2'){
        int numNodes;
        std::cout << "Enter a number of nodes: ";
        std::cin >> numNodes;
        tree.makeTreeSimple(numNodes);
    }
    else if(userOption == '3'){
        char arr[100];
        std::cout << "Enter character array: ";
        std::cin >> arr;
        tree.buildTreeFromArray(arr);
    }
    std::cout << "\n\n";
    tree.print();
    std::cout << '\n' << "Max depth of the tree: " << tree.getMaxDepth() << "\nNumber of nodes in tree: " << tree.getNumNodes() << '\n';
    int numNodesOnDL = tree.countNodesOnDeepestLevel();
    std::cout << "Number of nodes on the deepest level: " << numNodesOnDL << '\n';
    return 0;
}
