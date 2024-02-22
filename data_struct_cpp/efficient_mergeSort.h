#include <vector>
#include <cmath>
template <typename Comparable>
void mergeSort(std::vector<Comparable> & a){
    std::vector<Comparable> copy(a.begin(), a.end());
    int divdeLevel = std::ceil(std::log(a.size()));
    int height = 0;
    int sizeOfSmallerArray = 0;
    int leftPos, rightPos, rightEnd, tmpPos; // end is non-inclusive
    while(height < divideLevel){
        sizeOfSmallerArray = std::pow(2, height);
        leftPos = 0;
        tmpPos =  -1;
        rightPos = sizeOfSmallerArray;
        rightEnd = sizeOfSmallerArray * 2;
        for(rightEnd <= a.size()){
            while(leftPos < rightPos && rightPos < rightEnd){
                a[leftPos] < a[rightPos] ? 
                (tmpArray[++tmpPos] = std::move(a[leftPos++])) : (tmpArray[++tmpPos] = std::move(a[rightPos++]));
            }
            while(leftPos < rightPos){
                tmpArray[++tmpPos] = std::move(a[leftPos++]);
            }
            while(rightPos < rightEnd){
                tmpArray[++tmpPos] = std::move(a[rightPos++]);
            }
            leftPos = rightEnd;
            rightPos += sizeOfSmallerArray * 2;
            rightEnd += sizeOfSmallerArray * 2;
        }
        ++height;
    }
}