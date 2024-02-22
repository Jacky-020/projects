#include "left_heap.h"

int main(void){
    leftHeap<int> heap1;
    for(int i = 0; i < 20; i += 2){
        std::cout << i << ")\n";
        heap1.insert(i);
    }
    heap1.printHeap();
}