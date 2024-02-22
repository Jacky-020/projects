#include <vector>
#include <queue>
#include <iostream>

template <typename Comparable>
class BinomialQueue{
    public:
        BinomialQueue() : theTrees(DEFAULT_TREES), currentSize(0) {
            theTrees[0] = nullptr;
        }
        BinomialQueue(const Comparable & item) : theTrees(DEFAULT_TREES), currentSize(1){
            theTrees[0] = new BinomialNode(item);
        }
        BinomialQueue(BinomialQueue && rhs) : theTrees(rhs.theTrees.size()), currentSize(rhs.currentSize){
            for(int i = 0; i < rhs.theTrees.capacity(); ++i)
                theTrees[i] = std::move(rhs.theTrees[i]);
            for(auto & entry: rhs.theTrees)
                entry = nullptr;
            rhs.currentSize = 0;
        }
        BinomialQueue(Comparable arr[], int num){
            std::queue<BinomialQueue *> queueOfBQ;
            int i = 0;
            int mid = (num + 1) / 2;
            BinomialQueue * ptr, * ptr2;
            for(; i < mid; ++i){
                queueOfBQ.push(new BinomialQueue(arr[i]));
            }
            for(; i < num; ++i){
                ptr = queueOfBQ.front();
                queueOfBQ.pop();
                BinomialQueue temp(arr[i]);
                ptr->merge(temp);
                queueOfBQ.push(ptr);
            }
            while(queueOfBQ.size() > 1){

                ptr = queueOfBQ.front();
                queueOfBQ.pop();
                ptr2 = queueOfBQ.front();
                queueOfBQ.pop();

                ptr->merge(*ptr2);
                queueOfBQ.push(ptr);
            }
            auto BQ = queueOfBQ.front();
            theTrees.resize(BQ->theTrees.size());
            currentSize = BQ->currentSize;
            for(int i = 0; i < BQ->theTrees.size(); ++i)
                theTrees[i] = std::move(BQ->theTrees[i]);
        }

        bool isEmpty()const{
            return currentSize == 0;
        }
        const Comparable & findMin(){
            return theTrees[findMinIndex()]->element;
        }

        void insert(const Comparable & x){
            BinomialQueue temp(x);
            merge(temp);
        }
        void deleteMin(){
            if(isEmpty())
                return;
            int minIndex = findMinIndex();
            BinomialNode * deletedTree = theTrees[minIndex]->left;

            delete theTrees[minIndex];

            BinomialQueue deletedQueue;
            deletedQueue.theTrees.resize(minIndex + 1);
            deletedQueue.currentSize = (1 << minIndex) - 1;
            for(int j = minIndex -1; j >= 0; --j){
                deletedQueue.theTrees[j] = deletedTree;
                deletedTree = deletedTree->next;
                deletedQueue.theTrees[j]->next = nullptr;
            }
            theTrees[minIndex] = nullptr;
            currentSize -= deletedQueue.currentSize + 1;

            merge(deletedQueue);            
        }
        void deletedQueue(Comparable & minItem){
            if(isEmpty())
                return;
            int minIndex = findMinIndex();
            minItem = theTrees[minIndex]->element;
            BinomialNode * deletedTree = theTrees[minIndex]->left;

            delete theTrees[minIndex];

            BinomialQueue deletedQueue;
            deletedQueue.theTrees.resize(minIndex + 1);
            deletedQueue.currentSize = (1 << minIndex) - 1;
            for(int j = minIndex -1; j >= 0; --j){
                deletedQueue.theTrees[j] = deletedTree;
                deletedTree = deletedTree->next;
                deletedQueue.theTrees[j]->next = nullptr;
            }
            theTrees[minIndex] = nullptr;
            currentSize -= deletedQueue.currentSize + 1;

            merge(deletedQueue); 
        }
    
        void merge(BinomialQueue & rhs){
            if(this == &rhs)
                return;
            
            currentSize += rhs.currentSize;
            if(currentSize > capacity()){
                int oldNumTrees = theTrees.size(); 
                int newNumTrees = std::max(theTrees.size(), rhs.theTrees.size()) + 2;
                theTrees.resize(newNumTrees);
                for(int i = oldNumTrees; i < theTrees.size(); ++i)
                    theTrees[i] = nullptr;
            }
            int condition = 0;
            BinomialNode * carry = nullptr;
            for(int i = 0, j = 1; j <= currentSize; ++i, condition = 0, j *= 2){
                BinomialNode * t1 = theTrees[i];
                BinomialNode * t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

                if(t1)
                    ++condition;
                if(t2)
                    condition += 2;
                if(carry)
                    condition += 4;
                switch(condition){
                    case 0:
                    case 1:
                        break;
                    case 2:
                        theTrees[i] = t2;
                        rhs.theTrees[i] = nullptr;
                        break;
                    case 3:
                        carry = combineTrees(t1, t2);
                        theTrees[i] = rhs.theTrees[i] = nullptr;
                        break;
                    case 4:
                        theTrees[i] = carry;
                        carry = nullptr;
                        break;
                    case 5:
                        carry = combineTrees(carry, t1);
                        theTrees[i] = nullptr;
                        break;
                    case 6:
                        carry = combineTrees(carry, t2);
                        rhs.theTrees[i] = nullptr;
                        break;
                    case 7:
                        theTrees[i] = carry;
                        carry = combineTrees(t1, t2);
                        rhs.theTrees[i] = nullptr;
                        break;
                }
            }

            for(auto & entry : rhs.theTrees)
                entry = nullptr;
            rhs.currentSize = 0;
        }

        void printTrees()const{
            for(int i = 0, j = 1; j <= currentSize; ++i, j *= 2){
                if(theTrees[i]){
                    std::cout << i << ")\n";
                    printTrees(theTrees[i], 1);
                }
            }
        }
    private:
        struct BinomialNode{
            Comparable element;
            BinomialNode * left;
            BinomialNode * next;

            BinomialNode(const Comparable & e = {}, BinomialNode *l = nullptr, BinomialNode *r = nullptr) :
            element(e), left(l), next(r) {}
        };

        const static int DEFAULT_TREES = 1;

        std::vector<BinomialNode *>theTrees;
        int currentSize;



        BinomialNode * combineTrees(BinomialNode * n1, BinomialNode * n2){
            if(n1->element > n2->element)
                std::swap(n1, n2);
            n2->next = n1->left;
            n1->left = n2;
            return n1;
        }

        int findMinIndex()const{
            int i;
            int minIndex;

            for(int i = 0; theTrees[i] == nullptr; ++i);

            for(minIndex = i;i < theTrees.size(); ++i){
                if(theTrees[i] != nullptr && theTrees[i]->element < theTrees[minIndex]->element){
                    minIndex = i;
                }
            }
            return minIndex;
        }
        int capacity()const{
            return (1 << theTrees.capacity()) - 1;
        }

        void printTrees(const BinomialNode * t, int depth)const{
            if(t == nullptr)
                return;
            printTrees(t->left, depth + 1);
            for(int i = 0; i < depth; ++i){
                std::cout << " ";
            }
            std::cout << t->element << std::endl;
            printTrees(t->next, depth + 1);
        }
};