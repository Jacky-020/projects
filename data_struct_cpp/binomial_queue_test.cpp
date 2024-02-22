#include "binomialQueue.h"

int main(void){
    BinomialQueue<int> BQ(1);
    BQ.insert(4);
    int arr[] = {2, 5, 7, 9, 11, 34, 56, 12};
    BinomialQueue<int> BQ2(arr, sizeof(arr) / sizeof(int));
    BQ2.printTrees();
    BQ.merge(BQ2);
    BQ.printTrees();
}