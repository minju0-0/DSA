#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stdexcept>
using namespace std;

#include "BST.hpp"

class BSTree : public BST {
    node* root;
    int size;

    node* create_node(int n, node* p) {
        node* newNode = new node{n, p, nullptr, nullptr};
        size++;
        return newNode;
    }

    void inorder(node* n) {
        if (!n) return;
        inorder(n->left);
        cout << n->elem << " ";
        inorder(n->right);
    }

    void print_node(string prefix, node* n, string label = "") {
        if (n == nullptr) return;
        // Print current node
        cout << prefix << label << "+--> " << n->elem << endl;

        // Build new prefix for children
        string child_prefix = prefix;
        if (label.empty()) {
            // Root node - children start with base spacing
            child_prefix = "";
        } else {
            // Replace the label with continuation spacing
            child_prefix += "";  // 5 spaces to align with "L " or "R "
        }
        child_prefix += "|    ";

        // Left child
        if (n->left)
            print_node(child_prefix, n->left, "L ");
        // Right child
        if (n->right)
            print_node(child_prefix, n->right, "R ");
    }


    public:
    BSTree() {
        size = 0;
        root = nullptr;
    }

    node* getRoot() {
        return root;
    }

    node* left(node* p){
        return (p)? p->left : nullptr;
    }

    node* right(node* p){
        return (p)? p->right : nullptr;
    }

    node* addRoot(int n) {
        if (root) throw logic_error("Already has root");
        root = create_node(n, nullptr);
        return root;
    }

    //---first code---
    // node* insert(int n) {
    //     if (!root) {
    //         root = create_node(n, nullptr);
    //         return root;
    //     }
    //
    //     node* curr = root;
    //     while (curr->right || curr->left) {
    //         if (n < curr->elem && left(curr)) curr = curr->left;
    //         else if(n > curr->elem && right(curr)) curr = curr->right;
    //         else break;
    //     }
    //
    //     if (curr->elem == n) throw logic_error("Element already exists");
    //     node* newNode = create_node(n, curr);
    //     if (n < curr->elem) curr->left = newNode;
    //     else curr->right = newNode;
    //     return newNode;
    // }

    //---refined code---
    node* insert(int n) {
        if (!root) return root = create_node(n, nullptr);

        node* curr = root;
        while (true) {
            if (n == curr->elem) {
                curr->elem = n;
                return curr;
            }
            node*& next = (n < curr->elem) ? curr->left : curr->right;
            if (!next) return next = create_node(n, curr);
            curr = next;
        }
    }

    int remove(int num) {
        node* n = search(num);
        if (!n) throw logic_error("Element not found");
        node* p = n->parent;
        if (left(n) && right(n)) {
            node* toReplace = n->right;
            if (!toReplace->left) {
                toReplace->left = n->left;
                n->left->parent = toReplace;

            } else {
                while (toReplace->left) toReplace = toReplace->left;
                toReplace->parent->left = nullptr;
                toReplace->parent = p;
                toReplace->left = n->left;
                toReplace->right = n->right;
                if (!p) root = toReplace;
            }
            if (!p) {
                root = toReplace;
                root->parent = nullptr;
            }else {
                if (p->right == n) p->right = toReplace;
                else p->left = toReplace;
            }

        }else {
            node* child = left(n) ? left(n) : right(n);
            if (child) child->parent = p;
            if (!p) root = child;
            else if (p->left == n) p->left = child;
            else p->right = child;
        }

        delete n;
        size--;
        return num;
    }


    node* search(int n) {
        node* curr = root;
        while (curr) {
            if (curr->elem == n) return curr;
            if (n < curr->elem) curr = curr->left;
            else if (n > curr->elem) curr = curr->right;
        }
        return nullptr;
    }



    void print() {
        if (size == 0) {
            cout << "EMPTY" << endl;
            return;
        }
        cout << "Size: " << size << endl;
        print_node("", root);
        cout << "Inorder: ";
        inorder(root);
    }

void printPyramid() {
    if (!root) {
        cout << "EMPTY\n";
        return;
    }

    // 1) Compute tree height (levels count)
    int h = root->height();        // e.g. leaf->height() == 0, root->height() = h
    int levels = h + 1;            // number of levels

    // 2) Determine grid size (rows and cols)
    int rows = levels * 2 - 1;                 // value rows and connector rows between
    int cols = 1 << (h + 3);                   // 2^(h+3) gives plenty of horizontal room
    if (cols < 80) cols = 80;                  // ensure a reasonable minimum width

    // 3) Prepare grid (2D text canvas)
    vector<string> grid(rows, string(cols, ' '));

    // 4) Use simple stacks (vectors as stacks) to place nodes iteratively
    // Each entry: node pointer, row index, column index, horizontal offset for children
    vector<node*> stackN;
    vector<int> stackR;
    vector<int> stackC;
    vector<int> stackOff;

    stackN.push_back(root);
    stackR.push_back(0);
    stackC.push_back(cols / 2);
    stackOff.push_back(cols / 4);

    while (!stackN.empty()) {
        // pop last
        node* cur = stackN.back(); stackN.pop_back();
        int r = stackR.back(); stackR.pop_back();
        int c = stackC.back(); stackC.pop_back();
        int off = stackOff.back(); stackOff.pop_back();

        if (!cur) continue;

        // place node's value centered at column c on row r
        string val = to_string(cur->elem);
        int start = c - (int)(val.size() / 2);
        if (start < 0) start = 0;
        for (int i = 0; i < (int)val.size() && start + i < cols; ++i)
            grid[r][start + i] = val[i];

        // if not last level, draw connectors and push children
        if (r + 2 < rows) {
            int branchRow = r + 1;
            int childRow = r + 2;

            // left child
            if (cur->left) {
                int lc = c - off;
                int slashCol = c - off / 2; // position for '/'
                if (slashCol >= 0 && slashCol < cols) grid[branchRow][slashCol] = '/';
                // push left child (push right first so left is processed later - doesn't matter)
                stackN.push_back(cur->left);
                stackR.push_back(childRow);
                stackC.push_back(lc);
                stackOff.push_back(max(1, off / 2));
            }

            // right child
            if (cur->right) {
                int rc = c + off;
                int backslashCol = c + off / 2; // position for '\'
                if (backslashCol >= 0 && backslashCol < cols) grid[branchRow][backslashCol] = '\\';
                stackN.push_back(cur->right);
                stackR.push_back(childRow);
                stackC.push_back(rc);
                stackOff.push_back(max(1, off / 2));
            }
        }
    }

    // 5) Print grid trimming trailing spaces
    for (int i = 0; i < rows; ++i) {
        int last = (int)grid[i].find_last_not_of(' ');
        if (last == (int)string::npos) cout << "\n";
        else cout << grid[i].substr(0, last + 1) << "\n";
    }
}



};

