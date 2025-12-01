#include "node.hpp"

class BST {
public:
    virtual ~BST() = default;
    virtual node* addRoot(int) = 0;
    virtual node* insert(int) = 0;
    virtual node* left(node*) = 0;
    virtual node* right(node*) = 0;
    virtual node* search(int) = 0;
    virtual int remove(int) = 0;
    virtual void print() = 0;
    virtual void printPyramid() = 0;
};

