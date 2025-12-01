#include <stdexcept>
#include <iostream>
using namespace std;

struct node {
    int elem;
    node* parent;
    node** child;
    int num_child;

    int depth() {
        if (!this->parent) return 0;
        return 1 + this->parent->depth();
    }

    int height() {
        if (num_child == 0) return 0;

        int h = 0;
        for (int i = 0; i < num_child; i++) {
            int childH = child[i]->height();
            if (childH > h) h = childH;
        }
        return h + 1;
    }
};

class myGenTree {
    int size;
    node* root;

public:
    myGenTree() {
        size = 0;
        root = nullptr;
    }

    node* addRoot(int num) {
        if (root) throw logic_error("root already exists");
        root = new node{num, nullptr, new node*[10], 0;};
        size++;
        return root;
    }

    node* addChild(node* p, int num) {
        if (!p) return nullptr;
        node* newNode = new node{num, p, new node*[10], 0};
        p->child[p->num_child++] = newNode;
        size++;
        return newNode;
    }

    void remove(node* n) {
        if (!n) return;
        if (n->num_child != 0) {
            cout << to_string(n->elem) << " has children" << endl;
            return;
        }

        if (n == root) {
           root = nullptr;
        }else {
            node* p = n->parent;
            for (int i = 0; i<p->num_child; i++) {
                if (n == p->child[i]) {
                    for (int j = i; j < p->num_child - 1; j++) {
                        p->child[j] = p->child[j + 1];
                    }
                    break;
                }
            }
            p->num_child--;
        }
        delete[] n->child;
        delete n;
        size--;
    }
};

/*
// 1. Go to the opInput method.
// 2. Go to node.h's evaluate method.
#include <iostream>
#include "mybinarytree.hpp" // already implemented, though hidden.
using namespace std;

node* opInput(MyBinaryTree* tree, string prompt, node* parent);

int main(void) {
    MyBinaryTree* tree = new MyBinaryTree();
    char op;
    int input, ind;
    node* nodes[100];
    int res;
    tree->root = opInput(tree, "root", NULL);
    do {
        cout << "Op: ";
        cin >> op;
        switch (op) {
            case 'p':
                tree->print();
                break;
            case 'e':
                cout << "Answer: " << tree->evaluate() << endl;
                break;
            case 'x':
                cout << "Exiting" << endl;
                break;
            default:
                cout << "Invalid operation" << endl;
        }
    } while (op != 'x');
    return 0;
}

node* opInput(MyBinaryTree* tree, string prompt, node* parent) {
    string input;
    cout << "Enter " << prompt << ": ";
    cin >> input;

    node* newNode = nullptr;
    switch (input[0]) {
        // TODO add cases for operations and default case for numbers
        case '+':
        case '-':
        case '*':
        case '/':
            newNode = tree->create_node(input, parent);
            newNode->left = opInput(tree, "left of " + input, newNode);
            newNode->right = opInput(tree, "right of " + input, newNode);
            break;
        default:
            newNode = tree->create_node(input, parent);
    }

    return newNode;
}

#include <string>
#include <iostream>
#include <cmath>
using namespace std;

struct node {
    string elem;
    node* left;
    node* right;
    node* parent;

// 	bool isDigit(string str){
// 	    try{
// 	        int n = stoi(str);
// 	        return true;
// 	    }
// 	}

    // TODO evaluate method
    int evaluate() {
        if(isdigit(elem[0])){
            return stoi(elem);
        }
        switch(elem[0]){
            case '+':
                return left->evaluate() + right->evaluate();
            case '-':
                return left->evaluate() - right->evaluate();
            case '*':
                return left->evaluate() * right->evaluate();
            case '/':
                return left->evaluate() / right->evaluate();
        }
        return 0;
    }
};

 */
