#include "Tree.hpp"

int main(){
    Tree tree(15);
    tree.generateRandomTree();
    tree.print();
    std::cout << '\n' << "Max depth of the tree: " << tree.getMaxDepth() << "\nNumber of nodes in tree: " << tree.getNumNodes() << '\n';
    int nmnds = tree.countNodesInDeepestLevel();
    std::cout << "Number of nodes on the deepest level: " << nmnds << '\n';
    return 0;
}
