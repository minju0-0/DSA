#include <iostream>
#include <queue>
using namespace std;

struct node {
    int elem;
    node* parent;
    node* left;
    node* right;

    int height() {
        return 1 + max(left? left->height() : -1, right? right->height() : -1);
    }

    int depth() {
        if(!this->parent) return 0;
        return 1 + this->parent->depth();
    }
};


class myBinaryTree {
    int size;
    node* root;

    node* create_node(int val, node* parent) {
        node* newNode = new node{val, parent, nullptr, nullptr};
        size++;
        return newNode;
    }

public:
    myBinaryTree() {
        size = 0;
        root = nullptr;
    }

    node* left(node* n) {
        if (!n || !n->left) return nullptr;
        return n->left;
    }

    node* right(node* n) {
        if (!n || !n->right) return nullptr;
        return n->right;
    }

    node* sibling(node* n) {
        if (!n || n == root) return nullptr;
        node* p = n->parent;
        return (p->left == n)? p->right : p->left;
    }

    node* addRoot(int num) {
        if (root) throw logic_error("root already exist");
        root = create_node(num, nullptr);
        return root;
    }

    node* addLeft(node* p, int num) {
        if (!p || p->left) throw logic_error("left already exist");
        p->left = create_node(num, p);
        return left(p);
    }

    node* addRight(node* p, int num) {
        if (!p || p->right) throw logic_error("right already exist");
        p->right = create_node(num, p);
        return right(p);
    }

    int set(node* n, int num) {
        if (!n) return -1;
        int res = n->elem;
        n->elem = num;
        return res;
    }

    int remove(node* n) {
        if (!n) return -1;
        if (n->left && n->right) throw logic_error(to_string(n->elem) +" has 2 children");

        int res = n->elem;
        node* p = n->parent;
        node* child = (n->left)? n->left : n->right;

        if (child)  child->parent = p;
        if (!p) root = child;
        else if (p->left == n) p->left = child;
        else p->right = child;

        delete n;
        size--;
        return res;
    }

    void preOrder(node* r) {
        if (!r) return;
        cout << r->elem << " ";

        if (r->left) preOrder(r->left);
        preOrder(r->right);
    }

    void inOrder(node* r) {
        if (!r) return;
        if (r->left) inOrder(r->left);
        cout << r->elem << " ";
        inOrder(r->right);
    }

    void postOrder(node* r) {
        if (!r) return;
        if (r->left) postOrder(r->left);
        postOrder(r->right);
        cout << r->elem << " ";
    }

    void bfs(node* r) {
        if (!r) return;
        queue<node*> q;
        q.push(r);

        while (!q.empty()) {
            r = q.front();
            q.pop();
            cout << r->elem << " ";
            if (r->left) q.push(r->left);
            if (r->right) q.push(r->right);
        }
    }

    node* getRoot() {
        if (!root) return nullptr;
        return root;
    }

};
