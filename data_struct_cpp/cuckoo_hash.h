#include <functional>
#include <utility>
#include <iostream>
#include <vector>

template<typename Object>
class cuckoo{
    public:
        enum EntryType{ACTIVE, EMPTY};

        cuckoo(unsigned int size = 11) : arr1(nextPrime(size)), arr2(nextPrime(size)), currentSizeArr1(0), currentSizeArr2(0) {
            for(auto & entry : arr1){
                entry.info = EMPTY;
            }
            for(auto & entry : arr2){
                entry.info = EMPTY;
            }
        }

        bool insert(const Object &x){
            if(contain(x)){
                return false;
            }
            auto posX = myhash(x);
            HashEntry toBeEvicted(x, ACTIVE);
            std::swap(toBeEvicted, arr1[posX.first]);

            //evict the original item to arr2
            decltype(posX) posToBeEvicted;
            bool processingArr1 = false;
            std::vector<size_t> recordArr1;
            std::vector<size_t> recordArr2;
            while(toBeEvicted.info == ACTIVE){
                posToBeEvicted = myhash(toBeEvicted.element);
                if(processingArr1){
                    if(std::find(recordArr1.begin(), recordArr1.end(), posToBeEvicted.first) != recordArr1.end()){
                        rehash();
                        return insert(toBeEvicted.element);
                    }
                    recordArr1.push_back(posToBeEvicted.first);
                }else{
                    if(std::find(recordArr2.begin(), recordArr2.end(), posToBeEvicted.first) != recordArr2.end()){
                        rehash();
                        return insert(toBeEvicted.element);
                    }
                    recordArr2.push_back(posToBeEvicted.first);
                }
                if(processingArr1){
                    std::swap(toBeEvicted, arr1[posToBeEvicted.first]);
                }else{
                    std::swap(toBeEvicted, arr2[posToBeEvicted.second]);
                }
                processingArr1 = ~processingArr1;
            }
            return true;
        }
        bool contain(const Object &x)const{
            auto posX = myhash(x);
            const auto & entry1 = arr1[posX.first];
            const auto & entry2 = arr2[posX.second];
            return (entry1.info == ACTIVE && entry1.element == x) || (entry2.info == ACTIVE && entry2.element == x);
        }
        void print_pos(size_t pos, int num)const{
            if(num == 1){
                const auto & entry = arr1[pos];
                if(entry.info == EMPTY)
                    std::cout << "empty" << std::endl;
                else
                    std::cout << entry.element << std::endl;
            }else{
                const auto & entry = arr2[pos];
                if(entry.info == EMPTY)
                    std::cout << "empty" << std::endl;
                else
                    std::cout << entry.element << std::endl;
            }
        }
        void print()const{
            std::cout << "array 1)\n";
            for(const auto & entry : arr1){
                if(entry.info == EMPTY)
                    std::cout << "empty" << std::endl;
                else
                    std::cout << entry.element << " (" << myhash(entry.element).first << "," << myhash(entry.element).second << ")" << std::endl;;
            }
            std::cout << "array 2)\n";
            for(const auto & entry : arr2){
                if(entry.info == EMPTY)
                    std::cout << "empty" << std::endl;
                else
                    std::cout << entry.element << " (" << myhash(entry.element).first << "," << myhash(entry.element).second << ")" << std::endl;
            }
        }
    private:
        struct HashEntry{
            Object element;
            EntryType info;
            HashEntry(const Object & x = {}, EntryType i = EMPTY) : element(x), info(i) {}
            HashEntry(Object && x, EntryType i = EMPTY) : element(std::move(x)), info(i) {}
            HashEntry(const HashEntry & h) : element(h.element), info(h.info) {}
            HashEntry(HashEntry && h) : element(std::move(h.element)), info(std::move(h.info)) {}
            HashEntry & operator=(const HashEntry & h){
                if(&h == this){
                    return *this;
                }
                element = h.element;
                info = h.info;
                return *this;
            }
            HashEntry & operator=(HashEntry && h){
                if(&h == this){
                    return *this;
                }
                element = std::move(h.element);
                info = h.info;
                return *this;
            }
        };
        std::vector<HashEntry> arr1;
        std::vector<HashEntry> arr2;
        int currentSizeArr1;
        int currentSizeArr2;
        const int DIGS = 31;
        const int mersennep = (1 << DIGS) - 1;

        std::pair<size_t, size_t> myhash(const Object &x)const{
            std::hash<Object> hf;
            long long hashVal = hf(x);
            return std::make_pair(universalHash(hashVal, 1, 4, arr1.size()), universalHash(hashVal, 2, 4, arr2.size()));
        }
        size_t universalHash(int x, int A, int B, int M)const{
            long long hashVal = static_cast<long long>(A) * x + B;
            hashVal = (hashVal >> DIGS) + (hashVal & mersennep);
            if(hashVal >= mersennep)
                hashVal -= mersennep;
            return static_cast<int>(hashVal) % M;
        }
        int nextPrime(int num)const {
            while(isComposite(num)){
                ++num;
            }
            return num;
        }
        bool isComposite(int num)const {
            for(int i = 2; i < num; ++i){
                for(int j = i; j < num; ++j){
                    if(num == i * j){
                        return true;
                    }
                }
            }
            return false;
        }
        void rehash(){
            std::vector<HashEntry> oldArray = arr1;
            oldArray.insert(oldArray.end(), arr2.begin(), arr2.end());
            arr1.resize(nextPrime(2 * arr1.size()));
            arr2.resize(nextPrime(2 * arr2.size()));
            currentSizeArr1 = currentSizeArr2 = 0;
            for(auto & entry : arr1){
                entry.info = EMPTY;
            }
            for(auto & entry : arr2){
                entry.info = EMPTY;
            }
            for(const auto & entry : oldArray){
                if(entry.info == ACTIVE){
                    insert(entry.element);
                }
            }
        }
};