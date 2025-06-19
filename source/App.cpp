#include "../headers/App.h"
#include <iostream>


App::App(){};
App::~App(){};

void App::run(){
    RBTree tree;

    tree.insertValue(10);
    tree.insertValue(20);
    //tree.insertValue(30);

    tree.printVersion(0); // Print version 0
    tree.printVersion(1); // Print version 1
    tree.printVersion(2); // Print version 2
    tree.printVersion(3); // Print version 3 (after all inserts)

    return;
}

void App::test(){
    RBTree tree;
    
    // Step 1: Insert 11 values
    int initialInsertions[] = {20, 15, 25, 10, 18, 22, 30, 5, 12, 17, 19};
    for (int val : initialInsertions) {
        tree.insertValue(val);
    }
    std::cout << "Tree after 11 insertions:\n";
    tree.print();
    
    // Step 2: Delete one value
    tree.deleteValue(15); // This value has children (medium difficulty case)
    std::cout << "\nTree after deleting 15:\n";
    tree.print();
    
    // Step 3: Insert 6 more values
    int moreInsertions[] = {13, 14, 6, 21, 27, 33};
    for (int val : moreInsertions) {
        tree.insertValue(val);
    }
    std::cout << "\nTree after 6 more insertions:\n";
    tree.print();
    return;
}

