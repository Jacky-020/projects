#include <vector>
#include <iostream>

template <typename Comparable>
void mergeSort(std::vector<Comparable> & a);
template <typename Comparable>
void mergeSort(std::vector<Comparable> & a);
template <typename Comparable>
void mergeSort(std::vector<Comparable> & a, std::vector<Comparable> & tmpArray, int leftPos, int rightEnd, int depth, int & maxDepth);
template <typename Comparable>
void merge(std::vector<Comparable> & a, std::vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd);

template <typename Comparable>
void mergeSort(std::vector<Comparable> & a){
    std::vector<Comparable> tmpArray(a.begin(), a.end());
    int size = a.size() - 1;
    int maxDepth = 0;
    mergeSort(a, tmpArray, 0, size, 0, maxDepth);
    if(maxDepth & 1){
        a.swap(tmpArray);
    }
}

//depth is 0 initially
template <typename Comparable>
void mergeSort(std::vector<Comparable> & a, std::vector<Comparable> & tmpArray, int leftPos, int rightEnd, int depth, int & maxDepth){
    if(leftPos == rightEnd){
        if(depth > maxDepth){
            maxDepth = depth;
        }
        return;
    }
    int mid = (leftPos + rightEnd) / 2;
    mergeSort(tmpArray, a, leftPos, mid, ++depth, maxDepth);
    mergeSort(tmpArray, a, mid + 1, rightEnd, depth, maxDepth);
    merge(a, tmpArray, leftPos, mid + 1, rightEnd); //merge the deeper
}

template <typename Comparable>
void merge(std::vector<Comparable> & a, std::vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd){
    int l = leftPos, r = rightPos, currentPos = leftPos;

    while(l < rightPos && r <= rightEnd){
        (a[l] < a[r]) ? (tmpArray[currentPos++] = std::move(a[l++])) : (tmpArray[currentPos++] = std::move(a[r++]));
    }

    while(l < rightPos){
        tmpArray[currentPos++] = a[l++];
    }
    while(r <= rightEnd){
        tmpArray[currentPos++] = a[r++];        
    }
    for(int i = leftPos; i <= rightEnd; ++i){
        a[i] = tmpArray[i];
    }
}