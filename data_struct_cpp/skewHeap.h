#include <algorithm>
template<typename Object>
class skewHeap{
    private:
        struct Node{
            Object element;
            Node * left;
            Node * right;

            Node(Object & x = {}, Node * l = nullptr, Node * right = nullptr) :
            element(x), left(l), right(r) {}
        };

        Node * merge(Node * h1, Node * h2){
            if(h1 == nullptr)
                return h2;
            if(h2 == nullptr)
                return h1;
            if(h1->element < h2->element)
                return merge1(h1, h2);
            else 
                return merge1(h2, h1);
        }

        Node * merge1(Node * h1, Node * h2){
            if(h1->right == nullptr)
                h1->right = h2;
            else
                h1->right = merge(h1->right, h2);
            std::swap(h1->right, h1->left);
            return h1;
        }

        void printHeap(const Node * t, int depth)const{
            if(t == nullptr)
                return;
            printHeap(t->left, depth + 1);
            for(int i = 0; i < depth; ++i){
                std::cout << " ";
            }
            std::cout << t->element << std::endl;
            printHeap(t->right, depth + 1);
        }
        Node * root;
    public:
        skewHeap() : root(nullptr) {}

        const Object & findMin()const{
            return root->element;
        }

        void insert(Object & item){
            auto newNode = new Node(item);
            root = merge(root, newNode);
        }

        void deleteMin(){
            auto & temp = root;
            root = merge(root->left, root->right);
            delete temp;
        }

        void deleteMin(Object & minItem){
            minItem = root->element;
            deleteMin();
            return minItem;
        }
        void merge(leftHeap & rhs){
            if(*this == &rhs)
                return;
            root = merge(root, rhs.root);
            rhs.root = nullptr;
            return;
        }
        void printHeap()const{
            printHeap(root, 0);
        }
};