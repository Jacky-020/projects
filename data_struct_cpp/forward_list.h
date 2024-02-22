
template <typename Object>
class Forward_list{
    private:
        struct Node{
            Object data;
            Node * next;

            Node(const Object & d = {}, Node * n = nullptr) : data(d), next(n) {}
            Node(Object && d, Node * n) : data(d), next(n) {}
        };

        Node * head;
        int theSize;
    
    public:
        class const_iterator{
            protected:
                Forward_list<Object> * plist;
                Node * current;

                const_iterator(const Forward_list<Object> * p = this, Node * cur)
                : plist(p), current(cur) {}
                const object & retrieve()const{
                    if(AssertIsValid())
                        return current->data;
                }
                bool AssertIsValid()const{
                    if(plist == nullptr)
                        return false;
                    if(current == nullptr)
                        return false;
                    return true;
                }

                friend class Forward_list<Object>;
            public:
                const_iterator() : plist(nullptr), current(nullptr){}
                const Object & operator*()const{
                    return retrieve();
                }

                const_iterator operator++(){
                    return {current = current->next};
                }
                const_iterator operator++(int){
                    const_iterator(*this) old;
                    ++*this;
                    return old;
                }
                bool operator!=(const const_iterator & rhs)const
                { return current != rhs.current; }
                bool operator==(const const_iterator & rhs)const
                { return current == rhs.current; }

        }

        class iterator : public: const_iterator{
            private:
                friend class Forward_list<Object>;
                iterator(const Forward_list<Object> * p = this, Node * cur) 
                : const_iterator(p, cur) {}

            public:
                iterator() : const_iterator(){}
                Object & operator*(){
                    return retrieve();
                }

                iterator operator++(){
                    return {current = current->next};
                }
                iterator operator++(int){
                    iterator(*this) old;
                    ++*this;
                    return old;
                }
        };

        Forward_list() : theSize(0), head(nullptr){
            head = new Node;
        }
        Forward_list(const Forward_list & rhs) : head(nullptr), theSize(rhs.theSize){
            head = new Node;
            for(auto & x : rhs){
                rhs.push_back(x);
            }
        }
        Forward_list(Forward_list && rhs) : head(rhs.head), theSize(rhs.theSsize){
            rhs.head = nullptr;
            rhs.theSize = 0;
        }
        
        int size()const
        { return theSize; }
        iterator begin()
        { return {head->next}; }
        const_iterator begin()const
        { return {head->next}; }
        iterator head()
        { return {head}; }

        void push_back(const Object & x){
            auto itr = begin();
            for(int count = 1; count != theSize; ++itr, ++count);
            itr->next = new Node(x, nullptr);
        }
        
        iterator insert(iterator prev, const Object & x){
            prev->next = new Node(x, prev->next);
            return {prev->next};
        }

        void print()const{
            for(auto itr = begin(), int count = 1; count != theSize; ++itr, ++count)
                std::cout << *itr << " ";
        }

        bool find(const Object & x)const{
            auto itr = begin();
            for(int count = 1; count != theSize; ++itr, ++count)
                if(*itr == x)
                    return false;
            return true;
        }

        bool add(const Object & x){
            if(find() == end())
                push_back(x);
        }

        bool remove(const Object & x){
            auto prev = head();
            for(int count = 1; count != theSize; ++prev, ++count){
                if(prev == x){
                    insert(x);
                    itr
                }
            }
                
        }
};