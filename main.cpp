#include <iostream>
#include "tree.h"
#include "stack.h"
#include "Queue.h"

int main() {
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);
    QueueArray<int> queueArray = tree.buildQueue();
    StackArray<int> stackArray = tree.buildStack();
    while (!queueArray.isEmpty()) {
        std::cout << queueArray.deQueue() << " ";
    }
    std::cout << "\n";
    while (!stackArray.isEmpty()) {
        std::cout << stackArray.pop() << " ";
    }
    std::cout << "\n";
    BinarySearchTree<int> tree_to_compare1 , tree_to_compare2;
    tree_to_compare1.insert(1);
    tree_to_compare2.insert(1);
    tree_to_compare1.insert(2);
    std::cout <<( (tree_to_compare2 == tree_to_compare1) ? "equal" : "not equal")<<"\n";
    tree_to_compare2.insert(2);
    std::cout <<( (tree_to_compare2 == tree_to_compare1) ? "equal" : "not equal")<<"\n";
    return 0;
}
