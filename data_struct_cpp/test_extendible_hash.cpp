#include <vector>
#include <iostream>
#include "extendible_hash.h"
using namespace std;

int main(void){
    ExtendHash<int> extend_hash;
    for(int i = 0; i < 100; ++i){
        extend_hash.insert(i);
    }
    extend_hash.print();
}