#include <vector>
#include <iostream>
template <typename Comparable>
void quickSort(std::vector<Comparable> & a, int start, int end);

template <typename Comparable>
void quickSort(std::vector<Comparable> & a){
    quickSort(a, 0, a.size() - 1);
}

template <typename Comparable>
void quickSort(std::vector<Comparable> & a, int left, int right){
    if(left >= right){
        return;
    }
    int center = (left + right) / 2;

    std::cout << "(" << left << "," << center << "," << right << ") ";
    if(a[left] > a[center]){
        std::swap(a[left], a[center]);
    }
    if(a[left] > a[right]){
        std::swap(a[left], a[right]);
    }
    if(a[center] > a[right]){
        std::swap(a[center], a[right]);
    }
    std::swap(a[center], a[right - 1]);
    const Comparable pivot = a[right - 1];

    int i = left;
    int j = right - 1;

    for(;;){
        while(a[++i] < pivot) ;
        while(a[--j] > pivot) ;
        if(i < j){
            std::swap(a[i], a[j]);
        }else{
            break;
        }
    }
    std::cout << "s = " << i << ") "; 
    std::swap(a[i], a[right - 1]);

        for(int i = 0; i < a.size(); ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    quickSort(a, left, i - 1);
    quickSort(a, i + 1, right);
}
