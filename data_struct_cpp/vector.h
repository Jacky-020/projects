#include <iostream>
#include <stdexcept>
template<class T>
class Vector{
    private:
        T * arr;
        int size;
        int capacity;
    public:
        class const_iterator{
        protected:
            friend class Vector<T>;

            const Vector<T> *theVect;
            T * ptr;

            T &retreive()const{
                AssertIsValid();
                return *ptr;
            }

            const_iterator(const Vector<T> * vect, T * pt) : theVect(vect), ptr(pt) {};

            void AssertIsValid()const{
                if(theVect == nullptr || ptr == nullptr)
                    std::cerr<< "assert not valid.\n";//throw out_of_range("out of range\n");
            }
        public:
            const_iterator(): ptr(nullptr) {};

            const T& operator*()const{
                return retreive();
            }

            const_iterator & operator++(){
                ++ptr;
                return *this;
            }
            const_iterator  operator++(int){
                auto temp = *this;
                ++ptr;
                return temp;
            }
            const_iterator & operator--(){
                --ptr;
                return *this;
            }
            const_iterator operator--(int){
                auto temp = *this;
                --ptr;
                return temp;  
            }
            const_iterator operator+(int i){
                return const_iterator(this->theVect, ptr + i);
            }
            const_iterator operator-(int i){
                return const_iterator(this->theVect, ptr -i);
            }
            bool operator==(const const_iterator & itr){
                return ptr == itr.ptr;
            }
            bool operator!=(const const_iterator & itr)const{
                return ptr != itr.ptr;
            }
        };
        class iterator : public const_iterator{
        protected:
            friend class Vector<T>;
            iterator(const Vector<T> * vect, T * pt) : const_iterator(vect, pt){};

                    
        public:
            iterator() : const_iterator(nullptr, nullptr) {};
            const T& operator*()const{
                return const_iterator::retrieve();
            }

            T &operator*(){
                return const_iterator::retreive();
            }
            iterator & operator++(){
                ++(this->ptr);
                return *this;
            }

            iterator & operator--(){
                --(this->ptr);
                return *this;
            }
            iterator operator--(int){
                auto temp = *this;
                --(this->ptr);
                return temp;  
            }
            iterator operator+(int i){
                return iterator(this->theVect, this->ptr + i);
            }
            iterator operator-(int i){
                return iterator(this->theVect, this->ptr - i);
            }
            /*
            bool operator==(const const_iterator & itr){
                return this->ptr == itr.ptr;
            }
            bool operator!=(const const_iterator & itr)const{
                return this->ptr != itr.ptr;
            }*/
        };
        static const int SpadeCapacity = 16;
        Vector(int initSize = 0) : size(initSize), capacity(initSize + SpadeCapacity)
        {arr = new T[capacity];};
        Vector(const Vector & v) : size(v.size), capacity(v.capacity), arr(nullptr)
        {
            arr = new T[v.capacity]; 
            for(int k = 0; k < size; ++k)
                arr[k] = v.arr[k];
        }
        Vector(const Vector && v) : size(v.size), capacity(v.capacity), arr(v.arr){
            v.arr = nullptr;
            v.size = v.capacity = 0;
        }
        Vector & operator=(const Vector & v){
            /*if(this == &v){
                return *this;
            }
            delete []arr;
            size = v.size;
            capacity = v.capacity;
            arr = new arr[capacity];
            for(int k = 0; k < size; ++k)
                arr[k] = v.arr[k];*/
            Vector copy = v;
            std::swap(*this, copy);
            return *this;
        }
        Vector & operator=(Vector && v)
        {
            std::swap(size, v.size);
            std::swap(capacity, v.capacity);
            std::swap(arr, v.arr);
            return *this;
        }
        ~Vector()
        {delete []arr; }
        void Resize(int newSize){
            if(newSize > capacity)
                Reserve(newSize * 2);
            size = newSize;
        }
        void Reserve(int newCapacity){
            if(newCapacity < size)
                return;
            T * new_arr = new T[newCapacity];
            for(int k = 0; k < size; ++k){
                new_arr[k] = std::move(arr[k]);
            }
            capacity = newCapacity;
            std::swap(new_arr, arr);
            delete []new_arr;
        }
        T & operator[](int i) {return arr[i]; };
        const T & operator[](int i)const {return arr[i]; };
        T & at(int i){
                if(i > size - 1 || i < 0){
                    std::cerr << "out of range!\n";
                    return arr[0];
                }
            return arr[i];
        }

        const T & at(int i)const {
                if(i > size - 1 || i < 0){
                    std::cerr << "out of range!\n";
                    return arr[0];
                }
            return arr[i];
        }

        bool Empty()const {return size == 0; };
        int Size()const {return size; };
        int Capacity()const {return capacity; };

        void Push_Back(const T & t){
            if(++size > capacity)
                Reserve(size * 2);
            arr[size - 1] = t;
        }
        
        void Push_Back(T && t){
            if(++size > capacity)
                Reserve(size * 2);
            arr[size - 1] = std::move(t);
        }

        void Pop_Back() {--size; }

        const T & Back()const{
            return arr[size - 1];
        }

        iterator Insert(iterator itr, const T & t){
            ++size;
            if(size > capacity)
                Reserve(size * 2);
            
            for(iterator temp = end(); temp != itr; --itr){
                *temp = *(temp - 1);
            }
            *itr = t;
            return ++itr;
        }

        void Insert(iterator itr, Vector & v){
            size += v.size ;
            if(size < capacity)
                Reserve(size * 2);
            for(iterator temp = end(); temp != itr - 1; --temp){
                *(temp + v.size) = *temp;
            }
            iterator v_begin = v.begin();
            for(int i = 0; i < v.size; ++i){
                *(itr + i) = *v_begin;
            }
        }

        iterator Insert(iterator itr, T && t){
            ++size;
            if(size > capacity)
                Reserve(size * 2);
            
            for(iterator temp = end(); temp != itr; --itr){
                *temp = std::move(*(temp - 1));
            }
            *itr = std::move(t);
            return ++itr;            
        }

        void Insert(iterator itr, Vector && v){
            size += v.size;
            if(size < capacity)
                Reserve(size * 2);
            for(iterator temp = end(); temp != itr - 1; --temp){
                *(temp + v.size) = std::move(*(temp));
            }
            iterator v_begin = v.begin();
            for(int i = 0; i < v.size; ++i){
                *(itr + i) = std::move(*v_begin);
            }
        }

        void erase(iterator itr){
            for(iterator temp = itr; temp != end() - 1; ++temp){
                *temp = *(temp + 1);
            }
            --size;
        }

        void erase(iterator begin, iterator end){
            auto iteration_end = end;
            while(begin != iteration_end){
                *(begin++) = *(end++);
                --size;
            }

        }
        const_iterator & begin()const {return const_iterator(this, &arr[0]); };
        const_iterator & end()const {return const_iterator(this, &arr[size]); };

        iterator begin() {return iterator(this, &arr[0]); };
        iterator end() {return iterator(this, &arr[size]); };


};

/*
template <class T> class const_iterator{
    protected:
        friend class Vector<T>;
        const Vector<T> *theVect;
        T * ptr;
        T &retreive()const{
            AssertIsValid();
            return *ptr;
        }
        const_iterator(const Vector<T> & vect, T * pt) : theVect(vect), ptr(pt) {};
        void AssertIsValid()const{
            if(theVect == nullptr || ptr == nullptr)
                throw out_of_range("out of range\n");
        }
    public:
        const_iterator(): ptr(nullptr) {};

        const T& operator*()const{
            return retrieve();
        }

        const_iterator & operator++(){
            ++ptr;
            return *this;
        }
        const_iterator  operator++(int){
            auto temp = *this;
            ++ptr;
            return temp;
        }
        const_iterator & operator--(){
            --ptr;
            return *this;
        }
        const_iterator operator--(int){
            auto temp = *this;
            --ptr;
            return temp;  
        }
        const_iterator & operator+(int i){
            ptr =+ i;
            return *this;
        }
        const_iterator & operator-(int i){
            ptr =- i;
            return *this;
        }


};

template<class T>
class iterator : public const_iterator{
    protected:
        friend class Vector<T>;
        iterator(Vector<T> * vect, T * pt) : const_iterator(vect, pt){};

                
    public:
        iterator() : const_iterator(nullptr, nullptr) {};
        T& operator*()const{
            return const_iterator::retrieve();
        }

        const T &operator*(){
            return const_iterator::operator*();
        }
        iterator & operator++(){
            ++ptr;
            return *this;
        }

        iterator & operator--(){
            --ptr;
            return *this;
        }
        iterator operator--(int){
            auto temp = *this;
            --ptr;
            return temp;  
        }
        iterator & operator+(int i){
            ptr =+ i;
            return *this;
        }
        iterator & operator-(int i){
            ptr =- i;
            return *this;
        }
};*/
