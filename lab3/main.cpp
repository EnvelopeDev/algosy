#include "Tree.hpp"

int main(){
    Tree tree(15);
    tree.generateRandomTree();
    tree.print();
    std::cout << tree.getMaxDepth() << ' ' << tree.getNumNodes() << '\n';
    std::cout << tree.countNodesInDeepestLevel() << '\n';
    return 0;
}
