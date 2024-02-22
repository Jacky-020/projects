#include <vector>
#include <algorithm>
#include "insertionSort.h"

template <typename Comparable>
Comparable quickSelect(std::vector<Comparable> & a, const Comparable k){
    quickSelect(a, 0, a.size() - 1, k);
    return a[k];
}

template <typename Comparable>
void quickSelect(std::vector<Comparable> & a, int left, int right, const Comparable k){
    if(left + 10 <= right){    
        int center = (left + right) / 2;
        const Comparable pivot = median3(a[left], a[center], a[right - 1]);
        std::swap(a[center], a[right]);

        int i = left, j = right - 1;
        for(;;){
            while(a[++i] < pivot) ;
            while(a[--j] > pivot) ;
            if(i < j){
                std::swap(a[i], a[j]);
            }else{
                break;
            }
        }

        std::swap(a[i], a[right]);
        if(k <= i){
            return quickSelect(a, left, i - 1);
        }else if(k > i + 1){
            return quickSelect(a, i + 1, right);
        }
    }else{
        InsertionSort(a, left, right);
    }
}

template <typename Comparable>
Comparable median3(Comparable & left, Comparable & center, Comparable & right){
    if(left > center){
        std::swap(left, center);
    }
    if(center > right){
        std::swap(center, right);
    }
    if(left > right){
        std::swap(left, right);
    }
    return center;
}
