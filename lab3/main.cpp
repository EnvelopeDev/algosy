#include "Tree.hpp"

int main(){
    Tree tree(1);
    //tree.print();
    std::cout << tree.getMaxDepth() << ' ' << tree.getNumNodes() << '\n';
    return 0;
}
