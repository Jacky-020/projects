#include <vector>

/*
As arr[0] is used to store insert item,
arr[i] store i item insted of i - 1 item
arr[currentSize] store the last item

for array based heap, size / 2 is the last item at height 0 (which is arr[size / 2]) for both odd and even size,
because the first item is the root, odd size -> tree with even offspring, vice versa
*/

template <typename Object>
class binary_heap{
    private:

        int currentSize;
        std::vector<Object> arr;

        void percolate_down(int i){
            int hole = i;
            Object tmp = std::move(arr[i]);
            int child;
            for(;hole * 2 <= currentSize; hole = child){
                child = hole * 2;

                //determine whether the next destination is left child or right child
                if(child != currentSize && arr[child] > arr[child + 1]){
                    ++child;
                }

                //see if tmp is smaller than the child (the next destination), if it is, percolate
                if(arr[child] < tmp){
                    arr[hole] = std::move(arr[child]);
                }else{
                    break;
                }
            }
            arr[hole] = std::move(tmp);
        }
    
    public:
        binary_heap() : currentSize(0), arr(){}

        binary_heap(const Object ar[], int size) : currentSize(size), arr(size + 1){
            for(int i = 0; i < size; ++i){
                arr[i + 1] = ar[i];
            }

            for(int hole = size / 2; hole > 0; --hole){
                percolate_down(hole);
            }
        }
        
        void insert(const Object & x){
            if(currentSize + 1 > arr.capacity()){
                arr.resize(2 * currentSize);
            }

            int hole = ++currentSize;
            arr[0] = x;
            for(; x < hole / 2; hole /= 2){
                arr[hole] = std::move(arr[hole / 2]);
            }
            arr[hole] = std::move(arr[0]);
        }

        Object delete_min(Object & min){
            if(currentSize == 0){
                return;
            }
            min = arr[1];
            arr[1] = arr[currentSize--];
            percolate_down(1);
            return min;
        }

        void delete_min(){
            if(currentSize == 0){
                return;
            }
            arr[1] = arr[currentSize--];
            percolate_down(1);
        }

};