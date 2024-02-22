#include "hopscotch.h"
using namespace std;

int main(void){
    hopscotch<int> hop;
    for(int i = 0; i < 12; ++i){
        hop.insert(i);
    }
        hop.print();
}