#include <vector>
#include <functional>

template <typename Object>
class QuadHashTable{
    public:
        explicit QuadHashTable(int size = 101) : array(nextPrime(size)){
            makeEmpty();
        }

        bool contains(const Object & x)const{
            return isActive(findPos(x));
        }

        void makeEmpty(){
            currentSize = 0;
            for(auto & entry : array){
                entry.info = EMPTY;
            }
        }
        bool insert(const Object & x){
            int currentPos = findPos(x);
            if(array[currentPos].info == ACTIVE){
                return false;
            }

            array[currentPos].element = x;
            array[currentPos].info = ACTIVE;

            if(currentSize++ > array.size() / 2){
                rehash();
            }

            return true;
        }
        bool insert(Object && x){
            int currentPos = findPos(x);
            if(array[currentPos].info == ACTIVE){
                return false;
            }

            array[currentPos].element = std::move(x);
            array[currentPos].info = ACTIVE;

            if(currentSize++ > array.size() / 2){
                rehash();
            }
            
            return true;
        }
        bool remove(const Object & x){
            int currentPos = findPos(x);
            if(!isActive(currentPos)){
                return false;
            }

            array[currentPos].info = DELETED;
            return true;
        }
        void print_collision()const{
            std::cout << "Collision count of quadratic probing: " << collision << std::endl;
        }

        enum EntryType{ACTIVE, EMPTY, DELETED};

    private:
        struct HashEntry{
            Object element;
            EntryType info;
            HashEntry(const Object & e = Object{}, EntryType i = EMPTY) 
            : element{e}, info{i} {}
            HashEntry(Object && e, EntryType i = EMPTY)
            : element{std::move(e)}, info{i} {}
        };

        std::vector<HashEntry> array;
        int currentSize;
        int collision = 0;

        bool isActive(int currentPos)const{
            return array[currentPos].info == ACTIVE;
        }
        
        int findPos(const Object & x){
            int currentPos = myhash(x);
            int offset = 1;

            while(array[currentPos].info != EMPTY && array[currentPos].element != x){
                currentPos += offset;
                offset += 2;
                if(currentPos >= array.size()){
                    currentPos -= array.size();
                }
                ++collision;
            }

            return currentPos;
        }
        void rehash(){
            std::vector<HashEntry> oldArray = array;
            array.resize(oldArray.size() * 2);
            for(auto & entry : array){
                entry.info = EMPTY;
            }
            currentSize = 0;
            for(auto & oldEntry : oldArray){
                if(oldEntry.info == ACTIVE)
                    insert(oldEntry.element);
            }
        }

        size_t myhash(const Object & x)const{
            static std::hash<Object> hf;
            return hf(x) % array.size();
        }

        int nextPrime(int num){
            while(isComposite(num)){
                ++num;
            }
            return num;
        }
        bool isComposite(int num){
            for(int i = 2; i < num; ++i){
                for(int j = i; j < num; ++j){
                    if(num == i * j){
                        return true;
                    }
                }
            }
            return false;
        }
};