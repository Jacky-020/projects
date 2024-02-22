#include "list.h"
#include <iostream>
using namespace std;


int main(void){
    List<int> L1;
    for(int i = 0; i < 20; ++i){
        L1.push_back(i);
    }
    L1.erase(L1.begin());
    for(auto itr = L1.begin(); itr != L1.end(); ++itr)
        cout << *itr << " ";
    cout << endl;

    List<int>L2;
    for(int i  = 0; i < 20; ++i){
        L2.push_back(i * i);
    }
    for(auto itr = L2.begin(); itr != L2.end(); ++itr)
        cout << *itr << " ";
    cout << endl;

    L1.splice(L1.begin() + 6, L2);
    for(auto itr = L1.begin(); itr != L1.end(); ++itr)
        cout << *itr << " ";
    cout << endl;

    List<int>::reverse_iterator itr = L1.rbegin();
    while(itr != L1.rend())
        cout << *itr++ << " ";
    cout << endl;
}


