#include <stack>
#include <iostream>
template <typename Object>
class splay_tree{
    private:

        struct Node{
            Object element;
            Node * left;
            Node * right;

            Node(const Object & x = {}, Node * l = nullptr, Node * r = nullptr) : 
            element(x), left(l), right(r) {}
        };

        Node * root;
        int currentSize;

        void rotationWithLeftChild(Node *& parent){
            Node * child = parent->left;
            parent->left = child->right;
            child->right = parent;
            parent = child;
        }

        void rotationWithRightChild(Node *& parent){
            Node * child = parent->right;
            parent->right = child->left;
            child->left = parent;
            parent = child;
        }

        void doubleRotationWithLeftChild(Node *& parent){
            rotationWithRightChild(parent->right);
            rotationWithLeftChild(parent);
        }

        void doubleRotationWithRightChild(Node *& parent){
            rotationWithLeftChild(parent->left);
            rotationWithRightChild(parent);
        }
        
        void splay(Node *& bottom, Node *& middle, Node *& top){
            if(top->left == middle){
                if(middle->left == bottom){
                    rotationWithLeftChild(middle);
                    rotationWithLeftChild(top);
                }else{
                    doubleRotationWithLeftChild(top);
                }
            }else{
                if(middle->right == bottom){
                    //printTree();
                    rotationWithRightChild(middle);
                    //printTree();
                    rotationWithRightChild(top);
                }else{
                    doubleRotationWithRightChild(top);  
                }
            }
        }

        void printTree(const Node * t, int depth)const{
            if(t == nullptr){
                return;
            }
            printTree(t->left, depth + 1);
            for(int i = 0; i < depth; ++i)
                std::cout << "  ";
            std::cout << t->element << std::endl;
            printTree(t->right, depth + 1);
        }
    public:

        splay_tree() : root(nullptr), currentSize(0) {}

        bool insert(const Object & x){
            
            Node * theNode = root;

            if(theNode == nullptr){
                root = new Node(x);
                ++currentSize;
                return true;
            }
            Node * prev = nullptr;
            std::stack<Node **> pathRecord;
            pathRecord.push(&root);
            while(theNode){   
                prev = theNode;  
                if(x < theNode->element){
                    pathRecord.push(&(theNode->left));
                    theNode = theNode->left;
                }else if(x > theNode->element){
                    pathRecord.push(&(theNode->right));
                    theNode = theNode->right;
                }else{
                    return false;
                }
            }
            if(x < prev->element)
                prev->left = new Node(x);
            else{
                prev->right = new Node(x);
            }
            ++currentSize;
            //pathRecord.push_back(theNode);

            while(pathRecord.size() > 2){
                auto  bottom = pathRecord.top();
                pathRecord.pop();
                auto  middle = pathRecord.top();
                pathRecord.pop();
                auto  top = pathRecord.top();
                pathRecord.pop();
                splay(*bottom, *middle, *top);
            }
            return true;
        }


        bool find(const Object & x)const{
            const Node * theNode = root;
            while(theNode){
                if(x < theNode->element){
                    theNode = theNode->left;
                }else if(x > theNode->element){
                    theNode = theNode->right;
                }else{
                    return true;
                }
            }
            return false;
        }

        void printTree()const{
            printTree(root, 0);
        }
};