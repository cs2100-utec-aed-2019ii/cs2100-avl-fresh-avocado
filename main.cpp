#include "AVLTree.h"

int main() {
    
    auto* avlTree = new AVLTree<unsigned>();

    avlTree->insert(1);
    avlTree->insert(2);
    avlTree->insert(3);
    avlTree->insert(4);
    avlTree->insert(5);

    avlTree->print_level_order(avlTree->get_root());

    delete avlTree;

    return 0;
}