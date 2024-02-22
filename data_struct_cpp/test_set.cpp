#include "Set.h"
#include <iostream>
using namespace std;

int main(void){
    Set<int> num;
    for(int i = 0; i < 20; ++i){
        num.insert(i);
        cout << i << ")\n\n";
                    num.Print_in_tree();
                    cout <<endl;
    }
    for(int i = 7; i < 10; ++i){
        cout << "After erasing " << i << " )\n";
        num.erase(i);
        num.Print_in_tree();
        cout << endl;
    }

    for(auto itr = num.begin(); itr != num.end(); ++itr){
        cout << *itr << " ";
    }

}