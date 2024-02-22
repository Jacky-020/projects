#include <vector>
#include <forward_list>
#include <functional>

template <typename Object>
class separate_chaining_hash_table{
    private:
        std::vector<std::forward_list<Object>> array;
        int currentSize;

        int myhash(const Object & element)const{
            std::hash<Object> hf;
            return hf(element) % array.size();
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
        void rehash(){
            auto oldArray = array;
            array.resize(nextPrime(2 * array.size()));
            currentSize = 0;
            for(auto & theList : oldArray){
                for(auto & oldEntry : theList){
                    insert(oldEntry);
                }
            }
        }
    public:
        separate_chaining_hash_table(int size = 101) : array(nextPrime(size)), currentSize(size){}
        
        void makeEmpty(){
            for(auto & entry : array){
                delete entry;
            }
        }
        bool insert(const Object & element){
            auto theList = array[myhash(element)];
            for(auto & entry : theList){
                if(entry == element){
                    return false;
                }
            }
            if(theList.empty()){
                if(++currentSize >= array.size()){
                    rehash();
                }
            }
            theList.push_front(element);
            return true;
        }
        bool remove(const Object & element){
            auto theList = array[myhash(element)];
            for(auto itr = theList.begin(); itr != theList.end(); ++theList){
                if(*itr == element){
                    theList.erase(itr);
                    if(theList.empty()){
                        --currentSize;
                    }
                    return true;
                }
            }
            return false;
        }
        
};