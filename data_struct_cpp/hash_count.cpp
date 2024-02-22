#include "hash.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "quadrtic_hash.h"
#include "separate_chaining_hash.h"
using namespace std;

int main(void){
    srand(time(0));
    HashTable<int> linear_probing;
    QuadHashTable<int> quad_probing;
    separate_chaining_hash_table<int> separate;
    int input;
    for(int i = 0; i < 200; ++i){
        input = rand() % 10000;
        linear_probing.insert(input);
        quad_probing.insert(input);
        separate.insert(input);
    }
    linear_probing.print_collision();
    quad_probing.print_collision();
}