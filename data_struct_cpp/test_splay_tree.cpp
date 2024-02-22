#include "splay_tree.h"
using namespace std;

int main(void){
    splay_tree<int> tree;
    for(int i = 0; i < 20; ++i){
        tree.insert(i);
        std::cout << i << ")\n";
        tree.printTree();
        std::cout << std::endl;
    }
    tree.printTree();
}