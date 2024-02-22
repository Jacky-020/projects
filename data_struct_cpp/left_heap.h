#include <algorithm>
#include <iostream>

template <typename Object>
class leftHeap{
    private:

        struct Node{
            Object element;
            int npl;
            Node * left;
            Node * right;


            Node(Object x = {}, int nullPathLength = 0, Node * l = nullptr, Node * r = nullptr) :
            element(x), npl(nullPathLength), left(l), right(r) {}
        };

        Node * merge(Node * h1, Node * h2){
            if(h1 == nullptr)
                return h2;
            if(h2 == nullptr)
                return h1;
            if(h1->element > h2->element){
                return merge(h1, h2)
            }else{
                return merge(h2, h1);
            }

        }
        Node * merge2(Node * largerRoot, Node * smallerRoot){
            //need to check smallerRoot == nullptr as merge2 may swap
            if(smallerRoot == nullptr){
                return largerRoot;
            }
            if(smallerRoot->right == nullptr){
                smallerRoot->right = largerRoot;
            }

            if(largerRoot == nullptr){
                return smallerRoot;
            }
            if(smallerRoot->right->element > largerRoot->element){
                smallerRoot->right = merge(smallerRoot->right, largerRoot);

            }else{
                smallerRoot->left = merge(largerRoot, smallerRoot->right);
            }
            //make sure leftist, right path should be shorter
            if(smallerRoot->right->npl > smallerRoot->left->npl){
                std::swap(smallerRoot->right, smallerRoot->left);
            }
            smallerRoot->npl = smallerRoot->right->npl + 1;
            return smallerRoot;
        }
        
        void printHeap(const Node * t, int depth)const{
            if(!t)
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

        leftHeap() : root(nullptr) {}

        const Object & findMin()const{
            return root->element;
        }

        void insert(Object & item){
            auto newNode = new Node(item);
            if(root->element > newNode->element)
                root = merge(root, newNode);
            else
                root = merge(newNode, root);
        }

        void deleteMin(){
            auto & temp = root;
            if(root->left->element > root->right->element)
                root = merge(root->left, root->right);
            else
                root = merge(root->right, root->left);
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
            if(root->element > rhs.root->element){
                root = merge(root, rhs.root);
            }else{
                root = merge(rhs.root, root);
            }
            rhs.root = nullptr;
            return;
        }
        void printHeap()const{
            printHeap(root, 0);
        }
};