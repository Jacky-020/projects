#include <vector>
#include <utility>
#include <functional>
#include <iostream>
#include <iomanip>
template<typename Object>
class hopscotch{
    public:
        enum EntryType{ACTIVE, EMPTY};

        hopscotch(unsigned int size = 101, unsigned int max_offset = 3)
        : arr(nextPrime(size)), currentSize(0),MAX_OFFSET(max_offset){
            for(auto & entry : arr){
                entry.info = EMPTY;
            }
        }
        
        bool insert(const Object & x){
            if(find(x)){
                return false;
            }
            size_t pos = myhash(x);
            size_t offset;
            /*if((offset = offsetToNextVacant(pos)) <= MAX_OFFSET){
                writeHop(pos, offset);
                arr[newPosition(pos + offset)].element = x;
            }*/
            //std::cout << "pos:" << pos << " ";
            while((offset = offsetToNextVacant(pos)) > MAX_OFFSET){
            //std::cout << "offset:" << offset << " ";
                size_t next_vacant_position = newPosition(pos, offset);
                size_t position_to_be_evicted = newPosition(pos , offset - MAX_OFFSET);
                while(!canBeEvicted(position_to_be_evicted)){
                                            //std::cout << position_to_be_evicted << "\n";
                    if((position_to_be_evicted = newPosition(position_to_be_evicted, 1)) == next_vacant_position){
                        rehash();
                        return insert(x);
                    }
                }
            }
            writeHop(pos, offset);
            size_t new_pos = newPosition(pos, offset);
            arr[new_pos].element = x;
            arr[new_pos].info = ACTIVE;
            if(currentSize >= arr.size() / 2){
                rehash();
            }
            return true;
        }
        size_t findPos(const Object & x)const{
            size_t pos = myhash(x);
            unsigned long hop = arr[pos].hop;
            size_t offset = 0;
            do{
                if(hop & mask){
                    if(arr[pos + offset] == x){
                        return pos + offset;
                    }
                }
                ++offset;
            }while(hop <<= 1);
            return -1;
        }
        void print()const{
            int i = 0;
            std::cout << std::left;
            for(const auto & entry : arr){
                std::cout << std::setw(4) << i++ << ")    ";
                if(entry.info == ACTIVE) 
                    std::cout << std::setw(10) << entry.element;
                else    
                    std::cout << std::setw(10) << "empty";
                printBinary(entry.hop); 
                std::cout << std::endl;
            }
            std::cout << std::right;
        }
        bool find(const Object & x)const{
            size_t pos = myhash(x);
            for(int offset = 0; offset <= MAX_OFFSET; ++offset){
                if(isOpen(pos, offset)){
                    if(arr[newPosition(pos, offset)].element == x){
                        return true;
                    }
                }
            }
            return false;
        }
    private:
        struct HashEntry{
            Object element;
            unsigned long hop;
            EntryType info;

            HashEntry(const Object & x = {}, unsigned long h = 0, EntryType i = EMPTY)
            : element(x), hop(h), info(i){}
        };

        std::vector<HashEntry> arr;
        unsigned int currentSize;
        const unsigned int MAX_OFFSET;
        static const unsigned long mask = 1;

        size_t myhash(const Object & x)const{
            //std::hash<Object> hf;
            //return hf(x) % arr.size();
            return x % 10;
        }
        size_t offsetToNextVacant(size_t pos, size_t offset = 0)const{
            while(isOccupied(newPosition(pos, offset))){
                /*if(++offset > MAX_OFFSET){
                    return -1;
                }*/
                ++offset;
            }
            return offset;
        }
        bool isOccupied(size_t pos)const{
            /*size_t potential_original_position = (pos < MAX_OFFSET) ? 0 : pos - MAX_OFFSET;
            while(pos != potential_original_position){
                if(isOpen(pos, pos - potential_original_position))
                    return true;
                ++potential_original_position;
            }
            return false;*/
            return arr[pos].info == ACTIVE;
        }
        bool isOpen(size_t pos, size_t offset)const{
            return (arr[pos].hop << offset) & mask;
        }
        bool isOpen(unsigned long hop, size_t offset)const{
            return (hop << offset) & mask;
        }
        void writeHop(size_t pos, size_t offset){
            arr[pos].hop |= mask << offset;
        }
        void removeHop(size_t pos, size_t offset){
            arr[pos].hop &= ~(mask << offset);
        }
        bool canBeEvicted(size_t pos){
            size_t offset_obtained_from_hop = 0;
            size_t offset_to_vacant;
            while(offset_obtained_from_hop <= MAX_OFFSET){
                    if(isOpen(pos, offset_obtained_from_hop)){
                       if((offset_to_vacant = offsetToNextVacant(pos, offset_obtained_from_hop)) <= MAX_OFFSET){
                            size_t new_pos = newPosition(pos, offset_to_vacant);
                            size_t old_pos = newPosition(pos, offset_obtained_from_hop);
                            arr[new_pos].element = arr[old_pos].element;
                            arr[new_pos].info = ACTIVE;
                            arr[old_pos].info = EMPTY;
                            removeHop(pos, offset_obtained_from_hop);
                            writeHop(pos, offset_to_vacant);
                            return true;
                        }
                    }
                ++offset_obtained_from_hop;
            }
            return false;
        }
        size_t newPosition(size_t pos, size_t offset)const{
            size_t newPos = pos + offset;
            if(newPos > arr.size()){
                newPos -= arr.size();
            }
            return newPos;
        }

        void rehash(){
            std::vector<HashEntry> oldArray = arr;
            arr.resize(nextPrime(arr.size() * 2));
            
            for(auto & entry : arr){
                entry.info = EMPTY;
            }

            for(int pos = 0; pos < oldArray.size(); ++pos){
                if(oldArray[pos].hop == 0){
                    continue;
                }
                for(int offset = 0; offset <= MAX_OFFSET; ++offset){
                    if(isOpen(oldArray[pos].hop, offset)){
                        insert(oldArray[newPosition(pos, offset)].element);
                    }
                }
            }
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
        void printBinary(long i)const{
            std::string binary;
            for(int j = 0; j <= MAX_OFFSET; ++j){
                i % 2 ? binary += "1" : binary += "0";
                i /= 2;
            }
            for(auto itr = binary.begin(); itr != binary.end(); ++itr){
                std::cout << *itr;
            }
        }
};