#include <utility>
#include <iostream>
#include <ostream>
#include <stack>

template <typename Object>
class Binary_search_tree{
    private:
        struct Node{
            Object element;
            bool deleted;
            Node *left;
            Node *right;

            Node(Object elem = {}, bool del = false, Node *l = nullptr, Node *r = nullptr) :
            element(elem), deleted(del), left(l), right(r) {}
            
        };

        Node * root;
        int size;
        int deleted;

        void clear(Node *&t){
            if(t == nullptr)
                return;
            clear(t->left);
            clear(t->right);
            delete t;
        }
        bool insert(const Object &x, Node *&t){    
            if(t == nullptr){
                t = new Node(x);
                ++size;
                return true;
            }
            if(x < t->element){
                return insert(x, t->left);
            }else if(x > t->element){
                return insert(x, t->right);
            }else{
                if(t->deleted){
                    t->deleted = false;
                    --deleted;
                    return true;
                }else{
                    return false;
                }
            }
        }
        bool erase(const Object &x, Node *&t){ 
            if(t == nullptr){
                return false;
            }
            if(x < t->element){
                return erase(x, t->left);
            }else if(x > t->element){
                return erase(x, t->right);
            }else{
                if(t->deleted){
                    return false;
                }else{
                    t->deleted = true;
                    ++deleted;
                    if(empty()){
                        clear();
                    }
                    return true;
                }
            }
        }
        std::pair<const Node *, bool> findMin(const Node * t)const{
            if(t == nullptr){
                return {nullptr, false};
            }
            std::pair<const Node *, bool> retval = {nullptr, false};
            if(t->right == nullptr){
                retval = {t, t->deleted == false};
            }
            if(retval.second == false){
                retval = findMin(t->left);
            }
            if(retval.second == false){
                retval = {t, t->deleted == false};
            }
            if(retval.second == false){
                retval = findMin(t->right);
            }
            return retval;
        }
        std::pair<const Node *, bool> findMax(const Node *t)const{
            if(t == nullptr){
                return {nullptr, false};
            }
            std::pair <const Node *, bool> retval = {nullptr, false};     
            if(t->right == nullptr){
                retval = {t, t->deleted == false};
            }       
            if(retval.second == false){
                retval = findMax(t->right);
            }
            if(retval.second == false){
                retval = {t, t->deleted == false};
            }
            if(retval.second == false){
                retval = findMax(t->left);
            }

            return retval;
        }
        bool contains(const Object &x, const Node *t)const{
            if(t == nullptr){
                return false;
            }
            if(x < t->obj){
                return contains(x, t->left);
            }else if(x > t->element){
                return contains(x, t->right);
            }else{
                if(t->deleted == false){
                    return true;
                }else{
                    return false;
                }
            }
        }
        void PrintTree(std::ostream & out, const Node *t)const{
            if(t == nullptr)
                return;
            PrintTree(out, t->left);

            if(t->deleted == false){
                out << t->element << " ";
            }
            PrintTree(out, t->right);
        }
        Node * copy(Node *&t, Node *rhs){
            if(rhs == nullptr){
                return nullptr;
            }
            t = new Node(t.element, t.deleted, copy(t->left, rhs->left), copy(t->right, rhs->right));
        }
        void Print_more_info(const Node *t, int depth)const{
            if(t == nullptr)
                return;
            Print_more_info(t->left, depth + 1);
            for(int i = 0; i < depth; ++i) std::cout << ' ';
            std::cout << t->element << " ("<< depth <<")";
            t->deleted ? (std::cout << " deleted\n") : (std::cout << " exist\n");
            Print_more_info(t->right, depth + 1);
        }
        int Node_num(const Node *t)const{
            if(t == nullptr)
                return 0;
            int sum = Node_num(t->left);
            sum += Node_num(t->right);
            return ++sum;
        }
        int Leaf_num(const Node *t)const{
            if(t == nullptr)
                return 0;
            int sum = Leaf_num(t->right);
            sum += Leaf_num(t->left);
            if(t->right == nullptr || t->left == nullptr){
                ++sum;
            }
            return sum;
        }
        int Full_node_num(const Node *t)const{
            if(t == nullptr)
                return 0;
            int sum = Full_node_num(t->right);
            sum += Full_node_num(t->left);
            if(t->right && t->left){
                ++sum;
            }
            return sum;
        }
        void print(const Object &lower_bound, const Object &upper_bound, const Node *parent, const Node *thisNode)const{
            if(thisNode == nullptr){
                return;
            }
            if(parent != nullptr &&  thisNode->element < lower_bound){
                if(parent->element < lower_bound){
                    return;
                }
                print(lower_bound, upper_bound, thisNode, thisNode->right); 
            }else if(thisNode->element > upper_bound){
                if(parent != nullptr && parent->element < upper_bound){
                    return;
                }
                print(lower_bound, upper_bound, thisNode, thisNode->left); 
            }else{
                print(lower_bound, upper_bound, thisNode, thisNode->left);
                std::cout << thisNode->element << " ";
                print(lower_bound, upper_bound, thisNode, thisNode->right);
            }
        }


    public:
        Binary_search_tree() : root(nullptr), size(0), deleted(0) {}
        Binary_search_tree(const Binary_search_tree & rhs) : root(nullptr), size(rhs.size), deleted(rhs.deleted){
            root = copy(root, rhs.root);
        } 
        Binary_search_tree(Binary_search_tree &&rhs) : Binary_search_tree(){
            std::swap(root, rhs.root);
            std::swap(size, rhs.size);
            std::swap(deleted, rhs.deleted);
        }
        ~Binary_search_tree(){
            clear();
        }
        void clear(){
            clear(root);
            size = 0;
            deleted = 0;
            root = nullptr; 
        }
        bool empty()const{
            return tree_size() == 0;
        }
        int tree_size()const{
            return size - deleted;
        }

        bool insert(const Object &x){
            return insert(x, root);
        }

        bool erase(const Object &x){
            return erase(x, root);
        }
        const Object & findMin()const{
            return findMin(root).first->element;
        }
        const Object & findMax()const{
            return findMax(root).first->element;
        }
        bool contains(const Object &x)const{
            return contains(x, root);
        }
        void PrintTree(std::ostream & out = std::cout)const{
            PrintTree(out, root);
        }
        void Print_more_info()const{
            Print_more_info(root, 0);
        }
        int Node_num()const{
            return Node_num(root);
        }
        int Leaf_num()const{
            return Leaf_num(root);
        }
        int Full_node_num()const{
            return Full_node_num(root);
        }
        void print(const Object &lower_bound, const Object &upper_bound)const{
            print(lower_bound, upper_bound, nullptr, root);
        }
        void print_in_level()const{
            std::stack<const Node *> pointer_of_odd_level; 
            std::stack<const Node *> pointer_of_even_level;
            const Node * theNode;
            if(root != nullptr){
                pointer_of_odd_level.push(root);
            }
            while(!pointer_of_odd_level.empty() || !pointer_of_even_level.empty()){
                if(pointer_of_even_level.empty()){
                    while(!pointer_of_odd_level.empty()){
                        theNode = pointer_of_odd_level.top();
                        pointer_of_odd_level.pop();
                        std::cout << theNode->element << " ";
                        if(theNode->left != nullptr){
                            pointer_of_even_level.push(theNode->left);
                        }
                        if(theNode->right != nullptr){
                            pointer_of_even_level.push(theNode->right);
                        }
                    }
                }else{
                    while(!pointer_of_even_level.empty()){
                        theNode = pointer_of_even_level.top();
                        pointer_of_even_level.pop();
                        std::cout << theNode->element << " ";
                        if(theNode->left != nullptr){
                            pointer_of_odd_level.push(theNode->left);
                        }
                        if(theNode->right != nullptr){
                            pointer_of_odd_level.push(theNode->right);
                        }
                    }
                }
            }
        }
}; 