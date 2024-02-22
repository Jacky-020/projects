#include <iostream>
using namespace std;

typedef node *flist;

struct node{
    int i;
    node * next;
};

void Initialize(flist & pflist){
    pflist = new node;
    node * pnode = pflist;
    cout<<"Enter the list: ";
    while(cin >> pnode->i){
        pnode->next = new node;
        pnode = pnode->next;
    }
}

void Display(const flist & pflist){
    node * ptr = pflist;
    while(ptr)
    {
        cout << ptr->i << endl;
        ptr = ptr->next;
    }
}