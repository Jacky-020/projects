#include "Binary_search_tree_lazy.h"
#include <iostream>
using namespace std;

int main(void){
    Binary_search_tree<int> tree;
    for(int i = 0; i < 20; ++i){
        tree.insert(i);
    }
    tree.erase(7);
    tree.PrintTree();
    cout << "Min: " << tree.findMin() << ", Max: " << tree.findMax() << endl;
    cout << "Size: " ;
    for(int i = 0; i < 20; ++i){
        tree.erase(i);
    }
    for(int i = 0; i < 20; ++i){
        tree.insert(i * i);
    }
    for(int i = 0; i < 20; ++i){
        tree.insert(i);
    }
    tree.erase(361);
    tree.erase(0);
    tree.Print_more_info();

    cout << "Min: " << tree.findMin() << ", Max: " << tree.findMax() << endl;
        cout << "Node number: " << tree.Node_num() << endl;
        cout << "Leaf number: " << tree.Leaf_num() << endl;
        cout << "Full node number: " << tree.Full_node_num() << endl;
}