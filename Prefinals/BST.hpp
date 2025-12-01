#include "myBinaryTree.hpp"

class BST {
    myBinaryTree* tree;

    node* insert_node(node* n, int num) {
        if (!n || num == n->elem) return nullptr;
        return (num < n->elem)?
                (!n->left? tree->addLeft(n, num) : insert_node(n->left, num)) :
                (!n->right? tree->addRight(n, num) : insert_node(n->right, num));
    }

    node* getNode(int n) {
        node* root = tree->getRoot();
        while (root) {
            if (root->elem == n) return root;
            if (n < root->elem) root = root->left;
            else root = root->right;
        }
        return nullptr;
    }

public:
    BST() {
        tree = new myBinaryTree();
    }

    bool insert(int n) {
        node* root = tree->getRoot();
        if (!root) {
            tree->addRoot(n);
            return true;
        }
        return insert_node(root, n)? true : false;
    }

    bool search(int n) {
        node* root = tree->getRoot();
        while (root) {
            if (root->elem == n) return true;
            if (n < root->elem) root = root->left;
            else root = root->right;
        }
        return false;
    }

    bool remove(int num) {
        node* n = getNode(num);
        if (!n) return false;
        node* newVal = n;
        if (n->left && n->right) {
            newVal = n->right;
            while (newVal->left) newVal = newVal->left;
        }
        n->elem = newVal->elem;
        tree->remove(newVal);
        return true;
    }
};
