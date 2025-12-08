#include "gentreenode.hpp"
#include <iostream>
using namespace std;

class GenTree {
    public:
    virtual Node* addRoot(int) = 0;
    virtual Node* addChild(Node*, int) = 0;
    virtual int remove(Node*) = 0;
    virtual int getSize() = 0;
    virtual Node* getRoot() = 0;
    virtual void print() = 0;
};