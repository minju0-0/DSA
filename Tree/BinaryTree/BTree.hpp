#include <iostream>
#include "bTreeNode.hpp"
#include "BinaryTree.hpp"
using namespace std;
#include "bTreeNode.hpp"

class Btree {
    public:
    virtual ~Btree() = default;

    virtual node* left(node*) = 0;
    virtual node* right(node*) = 0;
    virtual node* sibling(node*) = 0;
    virtual node* addRoot(int) = 0;
    virtual node* addLeft(node*, int) = 0;
    virtual node* addRight(node*, int) = 0;
    virtual int set(node*, int) = 0;
    virtual int remove(node*) = 0;
    virtual node* search(int) = 0;
    virtual void print() = 0;
    virtual int getSize() = 0;
    virtual node* getRoot() = 0;
    virtual void preorder() = 0;
    virtual void inorder() = 0;
    virtual void postorder() = 0;
    virtual void breadthFirst() = 0;
    //virtual void attach(node*, BinaryTree*, BinaryTree*) = 0;
    
};