#include <functional>
#include <exception>
#include <iostream>
#include <iomanip>

template <typename Object>
class ExtendHash{
    public:
        ExtendHash(int directory_limit = 10) : DirectoryMaxSize(directory_limit) {
            directory.push_back(DirectoryEntry(0, new(std::vector<Object>)));
            directory.push_back(DirectoryEntry(1, new(std::vector<Object>)));
        }

        void insert(const Object & x){
            size_t offset = findOffset(x);
            if(directory[offset].ptr->size() >= DirectoryMaxSize){
                if(!split(offset)){
                    rehash();
                }
                return insert(x);
            }
            directory[offset].ptr->push_back(x);
        }

        void print()const{
            std::cout << std::left;
            for(const auto & entry : directory){
                std::cout << entry.key << ")\n";
                std::cout << std::setw(20) << "key value" << "Object" << std::endl;
                for(const auto & obj : *(entry.ptr)){
                    std::cout << std::setw(20) << makeKey(obj) << obj << std::endl;
                }
                std::cout << std::endl;
            }
            std::cout << std::right;
        }
    private:
        struct DirectoryEntry{
            std::vector<Object> * ptr;
            unsigned short key;

            DirectoryEntry(int key_number = 0, std::vector<Object> * p = nullptr) : key(key_number), ptr(p) {}
        };

        std::vector<DirectoryEntry> directory;
        const unsigned int DirectoryMaxSize;
        unsigned int currentSize = 0;
        unsigned int keySize = 1;

        size_t myhash(const Object & x)const{
            std::hash<Object> hf;
            return hf(x) % 10001;
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

        bool keyMatch(unsigned short key, unsigned long hashVal)const{
            return makeKey(hashVal, bitCount(key)) == key;
        }

        unsigned short makeKey(unsigned long hashVal)const{
            return hashVal & ~(SHRT_MAX << keySize);
        }

        size_t findOffset(const Object & x)const{
            unsigned short key = makeKey(myhash(x));
            for(size_t i = 0; i < directory.size(); ++i){
                if(key == directory[i].key){
                    return i;
                }
            }
            throw std::exception();
        }

        unsigned int bitCount(unsigned short key)const{
            unsigned int count = 0;
            while(key){
                ++count;
                key <<= 1;
            }
            return count;
        }

        void rehash(){
            auto oldDirectory = directory;
            directory.resize(2 * directory.size());
            if(++keySize > sizeof(short) * 8){
                throw std::exception();
            }
            for(unsigned short i = 0; i < directory.size(); ++i){
                directory[i].ptr = oldDirectory[i / 2].ptr;
                if(i % 2 == 0){
                    directory[i].key = oldDirectory[i / 2].key;
                }else{
                    directory[i].key = directory[i - 1].key + (1 << (keySize - 1));
                }
            }
        }

        bool split(size_t offset){
            size_t neighbour = (offset % 2) ? offset - 1 : offset + 1;
            if(directory[neighbour].ptr != directory[offset].ptr){
                return false;
            }

            std::vector<Object> thisDirectory;
            directory[neighbour].ptr = new(std::vector<Object>);
            for(auto & obj : *(directory[offset].ptr)){
                if(makeKey(obj) == directory[neighbour].key){
                    directory[neighbour].ptr->push_back(std::move(obj));
                }else{
                    thisDirectory.push_back(std::move(obj));
                }
            }
            directory[offset].ptr->swap(thisDirectory);
            return true;
        }
};