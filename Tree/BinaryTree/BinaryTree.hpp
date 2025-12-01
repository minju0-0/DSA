#include <iostream>
#include <stdexcept>
#include "BTree.hpp"
#include <queue>
using namespace std;


class BinaryTree{
    int size;
    node* root;

    // void print_node(string prefix, node* n){
    //     if(n == nullptr) return;
    //
    //     cout << prefix << "+--> " << n->elem << endl;
    //
    //     if(n->left){
    //         print_node(prefix + "|    ", n->left);
    //     }
    //     if(n->right){
    //         print_node(prefix + "|    ", n->right);
    //     }
    // }

    void print_node(string prefix, node* n, bool isLeft) {
        cout << prefix;
        cout << (isLeft ? "+--L: " : "+--R: " );
        cout << n->elem << endl;
        if (n->left) {
            print_node(prefix + "|   ", n->left, true);
        }
        if (n->right) {
            print_node(prefix + "|   ", n->right, false);
        }
    }


    node* get_node(node* n, int num){
        if(n == nullptr) return nullptr;
        //visit
        if(n->elem == num) return n;

        //check left
        if(n->left){
            if(node* found = get_node(n->left, num)) return found;
        }
        return get_node(n->right, num);
    }

    void pre(node* n){
        if(!n) return;

        //visit
        cout << n->elem << " -> ";
        //check left
        if(n->left) pre(n->left);
        //check right
        pre(n->right);
    }

    void in(node* n){
        if(!n) return;
        
        //check left
        if(n->left) in(n->left);
        //visit
        cout << n->elem << " -> ";
        //check right
        in(n->right);
    }

    void post(node* n){
        if(!n) return;

        //check left
        if(n->left) post(n->left);
        //check right
        post(n->right);
        //visit
        cout << n->elem << " -> ";
    }

    void BFS(node* r){
        if(!r) return;
        queue<node*> q;
        q.push(r);

        while(!q.empty()){
            node* curr = q.front();
            q.pop();
            cout << curr->elem << " -> ";
            if(curr->left){
                q.push(curr->left);
            }if(curr->right){
                q.push(curr->right);
            }
        }
    }

        //without queue
    void bfs(node* n){
        if(!n) return;

        if(!n->left) return;
        cout << n->left->elem << " -> ";

        if(!n->right) return;
        cout << n->right->elem << " -> ";

        if(n->left->left) bfs(n->left);       
        bfs(n->right);
    }

    public:
    BinaryTree(){
        size = 0;
        root = nullptr;
    }
    
    node* left(node* p){
        return (p)? p->left : nullptr;
    }

    node* right(node* p){
        return (p)? p->right : nullptr;
    }

    node* sibling(node* n){
        node* prnt = n->parent;
        if(!(prnt->left) || !(prnt->right)) return nullptr;
        return (prnt->left == n)? prnt->right : prnt->left;
    }

    node* addRoot(int n){
        if(root){
            throw logic_error("Already has root");
        }
        root = new node{n, nullptr, nullptr, nullptr};
        size++;
        return root;
    }

    node* addLeft(node* p, int n){
        if(p->left){
            throw logic_error("Already has left child");
        }
        node* newLeft = new node(n, p);
        p->left = newLeft;
        size++;
        return newLeft;
    }

    node* addRight(node* p, int n){
        if(p->right){
            throw logic_error("Already has right child");
        }
        node* newRight = new node(n, p);
        p->right = newRight;
        size++;
        return newRight;
    }

    int set(node* n, int num){
        if(!n) return -1;
        int toReplace= n->elem;
        n->elem = num;
        return toReplace;
    }

    //sir code
    // int remove(node* n){
    //     if (!n) return -1;
    //
    //     int num = n->elem;
    //     if (left(n) && right(n)) throw new logic_error("It has 2 children");
    //     if (!left(n) && !right(n)) {
    //         if (node* p = n->parent) {
    //             if (p->left == n) {
    //                 p->left = nullptr;
    //             }else {
    //                 p->right = nullptr;
    //             }
    //         }else {
    //             root = nullptr;
    //         }
    //
    //     }else {
    //         node* child = (left(n))? left(n) : right(n);
    //         if (node* p = n->parent) {
    //             if (p->left == n) {
    //                 p->left = child;
    //             }else {
    //                 p->right = child;
    //             }
    //             child->parent = p;
    //         }else {
    //             root = child;
    //             child->parent = nullptr;
    //         }
    //     }
    //     delete n;
    //     size--;
    //     return num;
    // }

    //refined
    int remove(node* n) {
        if (!n) return -1;
        if (left(n) && right(n)) throw logic_error("It has 2 children");

        int num = n->elem;
        node* child = left(n) ? left(n) : right(n);
        node* p = n->parent;

        if (child) child->parent = p;
        if (!p) root = child;
        else if (p->left == n) p->left = child;
        else p->right = child;

        delete n;
        size--;
        return num;
    }

    void attach(node* n, BinaryTree* t1, BinaryTree* t2) {
        if(!n || left(n) || right(n) || !t1 || t1->size == 0 || !t2 || t2->size == 0) return;

        n->left = t1->root;
        t1->root->parent = n;

        n->right = t2->root;
        t2->root->parent = n;

        size += t1->size + t2->size;
        t1->size = t2->size = 0;
        t1->root = t2->root = nullptr;
        delete t1;
        delete t2;

    }


    void print(){
        if(!root){
            cout << "EMPTY" << endl;
            return;
        }

        cout << "Size: " << size << endl;
        print_node("", root, false);

    }

    node* search(int num){
        return get_node(root, num);
    }

    int getSize(){
        return size;
    }

    node* getRoot(){
        return root;
    }

    void preorder(){
        cout << "Preorder: ";
        pre(root);
    }

    void inorder(){
        cout << "Inorder: ";
        in(root);
    }

    void postorder(){
        cout << "Postorder: ";
        post(root);
    }

    void breadthFirst(){
        cout << "BFS: ";
        BFS(root);
    }

};

