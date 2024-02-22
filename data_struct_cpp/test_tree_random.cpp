#include "Binary_search_tree_lazy.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main(void){
    srand(time(0));
    Binary_search_tree<int> tree;
    for(int i = 0; i < 20; ++i){
        tree.insert(rand() % 100);
    }
    tree.Print_more_info();
    cout << endl;
    tree.print(20, 60);
    cout << "\n\nprint in same level)\n";
    tree.print_in_level();
}