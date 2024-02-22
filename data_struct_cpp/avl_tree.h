#include <utility>

template <typename Object>
class Set{
    private:
        class Node{
            public:
                Object obj;
                int height;
                Node *left;
                Node *right;
                const int maxAllowedImballance = 1;

                Node(Object x = {}, int h = 0, left = nullptr, right = nullptr)
                : obj(x), height(h), left(nullptr), right(nullptr){}

                Node(const Node &n) 
                : obj(n.obj), height(n.height), left(obj.left), right(obj.right){}

                Node(Node &&n) : Node()
                { std::swap(*this, n); }

                ~Node() {}
        };
        Node * root;


        void remove(Node *t){
            if(t == nullptr)
                return;
            remove(t->left);
            remove(t->right);
            delete t;
        }
        void copy(Node *t,  const Node *rhs){
            if(t == nullptr)
                return;
            t = new(rhs)
            copy(t->left, rhs->left);
            copy(t->right, rhs->right);
        }

        bool find(const Node *t, const Object &x)const{
            if(t == nullptr)
                return false;
            if(x < t)
                return find(t->left, x);
            else if(x > t)
                return find(t->right, x);
            else    
                return true;
            
        }

        void insert(const Node*t, const Object &x){
            if(t == nullptr){
                t = new Node(x);
                return;
            }
                
            if(x < t)
                insert(t->left, x);
            else if(x > t)
                insert(t->right, x);
            else    
                return;
            balance(t);
        }

        void insert(const Node*t, Object &&x){
            if(t == nullptr){
                t = new Node(std::move(x), 0, );
                return;
            }
                
            if(x < t->obj)
                insert(t->left, std::move(x));
            else if(x > t->obj)
                insert(t->right, std::move(x));
            else    
                return;
            balance(t);
        }

        void erase(Node *&t, const Object &x){
            if(t == nullptr)
                return;
            
            if(x < t->obj)
                erase(t->left, x);
            else if(x > t->obj)
                erase(t->right, x);
            else if(t->left != nullptr && t->right != nullptr){
                Node * min_of_right = findMin(t->right);
                t->obj = min_of_right->obj;
                erase(min_of_right, min_of_right->obj);
            }else{
                Node *oldNode = t;
                t = t->left ? t->left : t->right;
                delete oldNode;
            }

            balance(t);
        }
        
        Node *findMin(Node *t){
            Node *ptr = t;
            for(; ptr->next != nullptr; ptr = ptr->left);
            return ptr;
        }

        void balance(Node *&t){
            if(t->left == nullptr && t->right == nullptr)
                return;
            int leftHeight = t->left ? t->left->height : -1;
            int rightHeight = t->right ? t->right->height : -1;
            if(leftHeight - rightHeight > maxAllowedImballance){
                int subLeftHeight = t->left->left ? t->left->left->height : -1;
                int subRightHeight = t->left->right ? t->left->right->height : -1;
                if(subLeftHeight > subRightHeight)
                    SingleRotationWithLeftChild(t);
                else
                    leftDoubleRotation(t);
            }
            else if(rightHeight - leftHeight > maxAllowedImballance){
                int subLeftHeight = t->right->left ? t->right->left->height : -1;
                int subRightHeight = t->right->right ? t->right->right->height : -1;
                if(subRightHeight > subLeftHeight)
                    SingleRotationWithRightChild(t);
                else
                    rightDoubleRotation(t);
            }
            t->height = max(leftHeight, rightHeight) + 1;
        }

        void SingleRotationWithLeftChild(Node *&t){
            Node *leftSubNode = t->left;
            t->left = leftSubNode->right;
            leftSubNode->right = t;
            t->height = max(t->left->height, t->right->height) + 1;
            t = leftSubNode;
            t->height = max(t->left->height, t->right->height) + 1;
        }

        void SingleRotationWithRightChild(Node *&t){
            Node *rightSubNode = t->right;
            t->right = rightSubNode->left;
            rightSubNode->left = t;
            t->height = max(t->left->height, t->right->height) + 1;
            t = rightSubNode;
            t->height = max(t->left->height, t->right->height) + 1;
        }

        void leftDoubleRotation(Node *&t){
            SingleRotationWithRightChild(t->left);
            SingleRotationWithLeftChild(t);
        }

        void rightDoubleRotation(Node *&t){
            SingleRotationWithLeftChild(t->right);
            righSingleRotation(t);
        }
    public:
        Set(){
            root = new Node();
        }

        ~Set(){
            remove(root);
        }
        Set(const Set &s){
            copy(root, s->root);
        }

        Set(Set &&s) : root(nullptr)
        { std::swap(root, this->root); }

        bool find(const Object& x)const{
            if(empty())
                return false;
            return find(root, x);
        }

        void insert(const Object &x){
            if(empty()){
                root = new Node;
                return;
            }
            if(find(x))
                return;
            insert(root, x);
        }

        void insert(Object &&x){
            if(empty()){
                root = new Node;
                return;
            }
            if(find(x))
                return;
            insert(root, std::move(x));
        }

        void erase(const Object &&x){
            if(empty())
                return;
            if(!find(x))
                return;
            erase(root, x);
        }

        bool empty()const
        { return root == nullptr; }
    
        
};