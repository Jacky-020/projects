#include <utility>
#include <iostream>
#include <algorithm>

template <typename Object>
class Set{
    private:
        static const int maxAllowedImballance = 1;

        class Node{
            public:
                Object obj;
                Node *left;
                Node *right;
                bool left_to_ancestor;
                bool right_to_ancestor;
                int height;

                Node(Object x = {}, Node *l = nullptr, Node *r = nullptr, bool left_linked = true, bool right_linked = true, int h = 0)
                : obj(x), left(l), right(r), left_to_ancestor(left_linked), right_to_ancestor(right_linked), height(h){}

                Node(const Node &n) 
                : obj(n.obj), left(obj.left), right(obj.right), left_to_ancestor(n.left_to_ancestor), 
                right_to_ancestor(n.right_to_ancestor), height(n.height){}

                Node(Node &&n) : Node()
                { std::swap(*this, n); }

                ~Node() {}
        };
        Node * root;

        class const_iterator{
            protected:
                Node *current;
                Set<Object> *theSet;

                const_iterator(Node *cur, Set<Object> *ptr_set = nullptr) : current(cur), theSet(ptr_set) {}

                bool AssertIsValid()const{
                    if (theSet == nullptr || this == nullptr){
                        std::cerr << "Improper access\n";
                        return false;
                    }
                    return true;
                }
                Object & retrieve()const{
                    if(AssertIsValid()){
                        return current->obj;
                    }
                    exit(EXIT_FAILURE);
                }

                friend class Set<Object>;

            public:
                const_iterator() : current(nullptr), theSet(nullptr) {}

                const Object & operator*()const{
                    return retrieve();
                }

                const_iterator operator++(){
                    if(current->right_to_ancestor == true){
                        current = current->right;
                    }else{
                        current = findMin(current->right);
                    }
                    return *this;
                }

                const_iterator operator++(int){
                    const_iterator old = *this;
                    operator++();
                    return old;
                }

                const_iterator operator--(){
                    if(current->left_to_ancestor == true){
                        current = current->left;
                    }else{
                        current = findMax(current->left);
                    }
                    return *this;
                }

                const_iterator operator--(int){
                    const_iterator old = *this;
                    operator--();
                    return old;
                }

                bool operator==(const const_iterator rhs)const{
                    return current == rhs.current;
                }

                bool operator!=(const const_iterator rhs)const{
                    return !operator==(rhs);
                }

                const_iterator operator=(const const_iterator rhs){
                    return {rhs.current, rhs.theSet};
                }
        };

        class iterator : public const_iterator{
            protected:
                iterator(Node *cur,Set<Object> *ptr_set = nullptr) : const_iterator(cur, ptr_set) {}

                friend class Set<Object>;
            
            public:
                iterator() : const_iterator(){}

                Object & operator*(){
                    return const_iterator::retrieve();
                }

                const Object & operator*()const{
                    return const_iterator::operator*();
                }

                iterator operator++(){
                    if(this->current->right_to_ancestor == true){
                        this->current = this->current->right;
                    }else{
                        this->current = findMin(this->current->right);
                    }
                    return *this;
                }

                iterator operator++(int){
                    return (*this)++;
                }

                iterator operator--(){
                    if(this->current->left_to_ancestor == true){
                        this->current = this->current->left;
                    }else{
                        this->current = findMax(this->current->left);
                    }
                    return *this;
                }

                iterator operator--(int){
                    return *(this)--;
                }
        };

        void remove(Node *t){
            if(t->left_to_ancestor == false)
                remove(t->left);
            if(t->right_to_ancestor == false)
                remove(t->right);
            delete t;
        }
        void copy(Node *t,  const Node *rhs){
            t = new Node(*rhs);
            if(t->left_to_ancestor == false)
                copy(t->left, rhs->left);
            if(t->right_to_ancestor == false)
                copy(t->right, rhs->right);
        }

        iterator find(const Node *t, const Object &x)const{
            if(x < t){
                if(t->left_to_ancestor == false){
                    return find(t->left, x);
                }
                else{
                    return end();
                }
            }else if(x > t){
                if(t->right_to_ancestor == false){
                    return find(t->right, x);
                }
                else{
                    return end();
                }
            }
            else    
                return iterator(t, this);
            
        }

        std::pair<iterator, bool> insert(Node *&t, const Object &x){  //forget to make t a reference, t need to be used in balance(Node *&t)
            std::pair<iterator, bool> retval;
            if(x < t->obj){
                if(t->left_to_ancestor == true){
                    t->left = new Node(x, nearest_proper_ancester_on_the_left(root, x), t); //IC: reverse the t and nearest
                    t->left_to_ancestor= false;
                    retval = {iterator(t->left, this), true}; //should not return directly as lacking one balnce() call
                }                                        // i.e. call at level 2 (parents of parents to nullptr) instead of level 1
                else{
                    retval = insert(t->left, x);
                }
            }
            else if(x > t->obj){
                if(t->right_to_ancestor == true){
                    t->right = new Node(x, t, nearest_proper_ancester_on_the_right(root, x));
                    //std::cout << "t = " << t->obj << " , left of " << t->right->obj << ": " << t->right->left->obj << std::endl;
                    t->right_to_ancestor = false;
                    retval = {iterator(t->right, this), true};
                }
                else{
                    retval = insert(t->right, x);
                }
            }
            else{
                return {iterator(t, this), false};
            }    

            balance(t);
            return retval;
        }

        std::pair<iterator, bool> insert(Node *&t, Object &&x){
            std::pair<iterator, bool> retval;
            if(x < t->obj){
                if(t->left_to_ancestor == true){
                    t->left = new Node(std::move(x), t, nearest_proper_ancester_on_the_right(root, x));
                    t->left_to_ancestor= false;
                    return {iterator(t->left, this), true};
                }
                else{
                    retval = insert(t->left, x);
                }
            }
            else if(x > t->obj){
                if(t->right_to_ancestor == true){
                    t->right = new Node(std::move(x), nearest_proper_ancester_on_the_left(root, x), t);
                    t->right_to_ancestor = false;
                    return {iterator(t->right, this), true};
                }
                else{
                    retval = insert(t->right, x);
                }
            }
            else{
                return {iterator(t, this), false};
            }    
            balance(t);
            return retval;
        }

        std::pair<iterator, bool> erase(Node *&t, const Object &x){
            std::pair<iterator, bool> retval;
            if(x < t->obj){
                if(t->left_to_ancestor == false)
                    retval = erase(t->left, x);
                else
                    return {end(), false};
            }
            else if(x > t->obj){
                if(t->right_to_ancestor == false)
                    retval = erase(t->right, x);
                else
                    return {end(), false};
            }
            else if(t->left_to_ancestor == false && t->right_to_ancestor == false){
                Node * min_of_right = findMin(t->right);
                t->obj = min_of_right->obj;
                erase(root->right, min_of_right->obj); //need to use root->right instead of min_of_right
                return {iterator(t, this), true};   //as need to change the value of its parent->left,  
            }else if(t->left_to_ancestor == false){  //need to pass parent->left to erase()
                Node *oldNode = t;
                t = t->left;
                Node *immediate_before = findMax(t);
                delete oldNode;
                immediate_before->right = nearest_proper_ancester_on_the_right(root, immediate_before->obj);
                retval = {iterator(t, this), true};
            }else if(t->right_to_ancestor == false){
                Node *oldNode = t;
                t = t->right;
                Node *immediate_next = findMin(t);
                std::cout << "oldNode ) " << oldNode  << " : " << oldNode ->obj <<std::endl;
                delete oldNode;
                immediate_next->left = nearest_proper_ancester_on_the_left(root, immediate_next->obj);
                                std::cout << "Immediate_next ) " << immediate_next->left  << " : " << immediate_next->left->obj <<std::endl;
                retval = {iterator(t, this), true};
            }else{
                Node *oldNode = t;
                Node *immediate_next = t->right;
                Node *immediate_before = t->left;
                Node *parent;
                bool oldNode_on_left_of_parent;
                if(immediate_next->left == t){
                    parent = immediate_next;
                    oldNode_on_left_of_parent = true;
                }else{
                    parent = immediate_before;
                    oldNode_on_left_of_parent = false;
                }
                delete oldNode;
                if(oldNode_on_left_of_parent == true){
                    parent->left = nearest_proper_ancester_on_the_left(root, immediate_next->obj);
                    parent->left_to_ancestor = true;

                }else{
                    parent->right = nearest_proper_ancester_on_the_right(root, immediate_before->obj);
                    parent->right_to_ancestor = true;
                }
                retval = {iterator(immediate_next, this), true};
            }

            balance(t);
            return retval; 
        }
        
        static Node *findMin(Node *t){
            Node *ptr = t;
            for(; ptr->left_to_ancestor == false; ptr = ptr->left);
            return ptr;
        }

        static Node *findMax(Node *t){
            Node *ptr = t;
            for(; ptr->right_to_ancestor == false; ptr = ptr->right);
            return ptr;
        }

        void balance(Node *&t){
            if(LeftHeight(t) - RightHeight(t) > maxAllowedImballance){

                if(LeftHeight(t->left) >= RightHeight(t->left))
                    SingleRotationWithLeftChild(t);
                else
                    leftDoubleRotation(t);
            }
            else if(RightHeight(t) - LeftHeight(t) > maxAllowedImballance){
                if(RightHeight(t->right) >= LeftHeight(t->right))
                    SingleRotationWithRightChild(t);
                else
                    rightDoubleRotation(t);
            }
            t->height = std::max(LeftHeight(t), RightHeight(t)) + 1;
            std::cout << "height of " << t->obj << ": " << t->height << std::endl;
            std::cout << "height of root = " << root->obj << ": " << root->height << std::endl;
        }

        int LeftHeight(const Node *t)const{
            return (t->left_to_ancestor == false) ? t->left->height : -1;
        }

        int RightHeight(const Node *t)const{
            return (t->right_to_ancestor == false) ? t->right->height : -1;
        }
        void SingleRotationWithLeftChild(Node *&t){
            Node *leftSubNode = t->left;
            t->left_to_ancestor = leftSubNode->right_to_ancestor;
            t->left = (t->left_to_ancestor) ? leftSubNode->right : nearest_proper_ancester_on_the_left(root, t->obj);
            if(t->left_to_ancestor == true){
                if(t->left == nullptr || t->left->obj < leftSubNode->left->obj)
                    t->left = leftSubNode;
            }
            leftSubNode->right = t;
            leftSubNode->height = std::max(LeftHeight(leftSubNode), RightHeight(leftSubNode)) + 1;
            t->height = std::max(LeftHeight(t), RightHeight(t)) + 1;
            t = leftSubNode;
        }

        void SingleRotationWithRightChild(Node *&t){
            Node *rightSubNode = t->right;
            t->right_to_ancestor = rightSubNode->left_to_ancestor;
            t->right = (t->right_to_ancestor == false) ? rightSubNode->left : nearest_proper_ancester_on_the_right(root, t->obj) ; // check if rightSubNode is a leaf
            if(t->right_to_ancestor == true){
                if(t->right == nullptr || t->right->obj < rightSubNode->right->obj) // either ancestor or the original next node
                    t->right = rightSubNode;
            }
            rightSubNode->left = t;
            rightSubNode->left_to_ancestor = false;
            rightSubNode->height = std::max(LeftHeight(rightSubNode), RightHeight(rightSubNode)) + 1;
            t->height = std::max(LeftHeight(t), RightHeight(t)) + 1;

            //std::cout << std::endl << "after balance: " << std::endl;
            //Print_more_info(rightSubNode->left);
            //Print_more_info(rightSubNode);
            //Print_more_info(rightSubNode->right);
            //std::cout << "\n Or \n\n";
            //Print_in_tree(rightSubNode, 0);
            //std::cout << "rightSubNode: " << rightSubNode->obj << std::endl;
            t = rightSubNode;


/*
            std::cout << "root: " << std::endl;
            Print_in_tree();
            std::cout << std::endl << std::endl;*/
        }

        void leftDoubleRotation(Node *&t){
            SingleRotationWithRightChild(t->left);
            SingleRotationWithLeftChild(t);
        }

        void rightDoubleRotation(Node *&t){
            SingleRotationWithLeftChild(t->right);
            SingleRotationWithRightChild(t);
        }

        Node *nearest_proper_ancester_on_the_right(Node *t, const Object &x){
            Node *retval = nearest_ancester_on_the_right(t, x, nullptr);
            if(retval->obj == x)
                retval == nullptr;
            return retval;
        }
        Node *nearest_ancester_on_the_right(Node *t, const Object &x, Node *retval){
            if(t->obj > x && t->right_to_ancestor == false){
                retval = t;
                return nearest_ancester_on_the_right(t->left, x, retval);
            }else if(t->obj < x && t->right_to_ancestor == false){
                return nearest_ancester_on_the_right(t->right, x, retval);
            }else{
                return retval;
            }
        }

        Node *nearest_proper_ancester_on_the_left(Node *t, const Object &x){
            Node *retval = nearest_ancester_on_the_left(t, x, nullptr);
            if(retval->obj == x)
                retval == nullptr;
            return retval;
        }
        Node *nearest_ancester_on_the_left(Node *t, const Object &x, Node *retval){
            if(t->obj > x && t->left_to_ancestor == false){
                return nearest_ancester_on_the_left(t->left, x, retval);
            }else if(t->obj < x && t->left_to_ancestor == false){
                retval = t;
                return nearest_ancester_on_the_left(t->right, x, retval);
            }else{
                return retval;
            }
        }

        static void Print_in_tree(const Node *t, int depth){
            if(t->left_to_ancestor == false){
                Print_in_tree(t->left, depth + 1);  //Ic: add return, so other part of the function is not executed
            }
            for(int i = 0; i < depth; ++i) std::cout << "  ";
            Print_more_info(t);
            if(t->right_to_ancestor == false){
                Print_in_tree(t->right, depth + 1);
            }
        }

        void static Print_more_info(const Node *t){
            std::cout << t->obj << " " ;
            if(t->left)
            std::cout << "left: " << t->left->obj << " ";
            if(t->right)
            std::cout << "right: " << t->right->obj << " ";
            std::cout << (t->left_to_ancestor ? "true" : "false") << " " << (t->right_to_ancestor ? "true" : "false") << std::endl;
        }
    public:
        Set() : root(nullptr) {}

        ~Set(){
            remove(root);
        }
        Set(const Set &s){
            copy(root, s->root);
        }

        Set(Set &&s) : root(nullptr)
        { std::swap(root, this->root); }

        const_iterator begin()const{
            return {findMin(root), this};
        }
        
        iterator begin(){
            return {findMin(root), this};
        }

        const_iterator end()const{
            return {nullptr, this};
        }

        iterator end(){
            return {nullptr, this};
        }

        iterator find(const Object& x)const{
            if(empty())
                return end();
            return find(root, x);
        }

        std::pair<iterator, bool> insert(const Object &x){
            if(empty()){
                root = new Node(x);
                return {iterator(root), true};
            }
            return insert(root, x);;
        }

        std::pair<iterator, bool> insert(Object &&x){
            if(empty()){
                root = new Node(std::move(x));
                return {iterator(root), true};
            }
            return insert(root, std::move(x));
        }

        std::pair<iterator, bool> insert(iterator hint, const Object &x){
            if(empty()){
                root = new Node(x);
                return {iterator(root), true};
            }
            auto retval = insert(hint, x);
            if(retval.second == false){
                retval = insert(root, x);
            }
            return retval;                                                      
        }

        std::pair<iterator, bool> insert(iterator hint, const Object &&x){
            if(empty()){
                root = new Node(std::move(x));
                return {iterator(root), true};
            }
            auto retval = insert(hint, std::move(x));
            if(retval.second == false){
                retval = insert(root, std::move(x));
            }   
            return retval;
        }

        std::pair<iterator, bool> erase(const Object &x){
            if(empty())
                return {end(), false};
            return erase(root, x);
        }

        bool empty()const
        { return root == nullptr; }
    
        void Print_in_tree()const{
            if(!empty()){          
                Print_in_tree(root, 0);
            }

        }
};