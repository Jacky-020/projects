#include "quickSort.h"
#include <iostream>
using namespace std;

int main(void){
    vector<int> arr{1, 3, 2, 5, 6 ,7 ,11 , 43, 23, 63, 44, 22};
    quickSort(arr);
    for(auto & item : arr)
        cout << item << " ";
}