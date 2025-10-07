#include "Tree.hpp"

int main(){
    Tree tree(10);
    tree.generateRandomTree();
    tree.print();
    std::cout << tree.getMaxDepth() << ' ' << tree.getNumNodes() << '\n';
    return 0;
}
