#include "GenTree.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>
using namespace std;

class MyGenTree : public GenTree {
    int size;
    int cap;
    Node* root;

    void print_node(string prefix, Node* n){
        cout << prefix << "+-->: " << n->elem << endl;
        for(int i = 0; i < n->numOf_child; i++){
            print_node(prefix + "    |", n->children[i]);
        }
    }

    Node* search(Node* n, int num) {
        if(n == nullptr){
            return nullptr;
        }

        if(n->elem == num){
            return n;
        }

        for(int i = 0; i<n->numOf_child; i++){
            Node* found = search(n->children[i], num);
            if(found != nullptr){
                return found;
            }
        }

        return nullptr;
    }

    /*
    search for the node with value 9
    +-->: 1
        +-->: 2
            +-->: 5
            +-->: 6
        +-->: 3
            +-->: 7
            +-->: 8
                +-->: 9
        +-->: 4

    1. search(root) → not 9 → go to root->child[0](2);
    2. search(two) → not 9 → go to two->child[0](5);'
    3. search(five) → not 9 → no children → return nullptr
    4. back to two → next child → two->child[1](6);
    5. search(six) → not 9 → no children → return nullptr
    6. back to 2 → all children done → return nullptr
    7. back to root → next child → root->child[1](3);
    8. search(three) → not 9 → go to three->child[0](7);
    9. search(seven) → not 9 → no children → return nullptr
    10. back to three → next child → three->child[1](8);
    11. search(eight) → not 9 → go to eight->child[0](9);
    12. search(nine) → nine->elem == → FOUND (returns pointer to node nine)
    13. return propagates upward: 9 → 8 → 3 → 1 → caller

    Final result: pointer to node 9 returned.
    Visited order: 1 → 2 → 5 → 6 → 3 → 7 → 8 → 9 (then stops)
    */

    public:
    MyGenTree() {
        cap = 10;
        size = 0;
        root = nullptr;
    }

    Node* addRoot(int num){
        if(root){
            throw logic_error("Already has root");
        }
        root = new Node{num, nullptr, (Node**)malloc(10 * sizeof(Node*)), 0, 5};
        size++;
        return root;
    }

    Node* addChild(Node* p, int num){
        int pCap = p->cap;
        int pSize = p->numOf_child;
        
        if (pSize >= ceil(pCap * 0.6)) { // if the number of children of the parent node exceeds or equal to 60% of the parents nodes children capacity
            p->cap += ceil(cap * 0.5); // resize the capacity of children array, add 50% of it
            p->children = (Node**)realloc(p->children, p->cap * sizeof(Node*)); 
        }

        Node* newChild = new Node{num, p, (Node**)malloc(10 * sizeof(Node*)), 0, 5};
        p->children[p->numOf_child++] = newChild;

        return newChild;
    }

    int remove(Node* n){
        return 0;
    }

    void removeLeaf(Node* n){
        if(n->numOf_child > 0){
            return;
        }

        Node* p = n->parent;
        for(int i = 0; i<p->numOf_child; i++){
            if(n == p->children[i]){
                for(int j = i; j<p->numOf_child - 1; j++){
                    p->children[j] = p->children[j + 1];
                }
            }
        }

        p->numOf_child--;
        delete[] n->children;
        delete(n);
        size--;
        return;
    }

    int getSize(){
        return size;
    }

    Node* getRoot() {
        return root;
    }

    void print() {
        cout << "Size: " << getSize() << endl;
        if(!getRoot()) {
            cout << "EMPTY" << endl;
            return;
        }
        print_node("", getRoot());
    }
    
    Node* getNode(int num) {
        return search(root, num);
    }


    
};