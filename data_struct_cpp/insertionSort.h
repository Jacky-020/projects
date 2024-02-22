#include <vector>
#include <algorithm>

template <typename Comparable>
void InsertionSort(std::vector<Comparable> & a){
    for(int p = 1; p < a.size(); ++p){
        Comparable tmp = std::move(a[p]);
        int i;
        for(i = p; i > 0 && tmp < a[i - 1]; --i){
            a[i] = std::move[i - 1];
        }
        a[i] = std::move(tmp);
    }
}

template <typename Comparable>
void InsertionSort(std::vector<Comparable> & a, int left, int right){
    int rightEnd = right + 1;
    for(int p = left + 1; p < rightEnd; ++p){
        Comparable tmp = std::move(a[p]);
        int i;
        for(i = p; i > left && tmp < a[i - 1]; --i){
            a[i] = std::move[i - 1];
        }
        a[i] = std::move(tmp);
    }
}