#include "cuckoo_hash.h"
#include <iostream>
using namespace std;

int main(void){
    cuckoo<int> hash(1);
    for(int i = 1; i < 20; ++i){
        hash.insert(i);
        //hash.print();
    }
    hash.print();
}