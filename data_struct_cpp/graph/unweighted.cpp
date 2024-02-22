#include "unweighted.h"
#include <iostream>
using namespace std;

int main(){
    graph<int> unweight_graph;
    unweight_graph.input();
    unweight_graph.unweighted(unweight_graph.inputVertex(1));
    unweight_graph.printShortest(unweight_graph.inputVertex(5));
}
