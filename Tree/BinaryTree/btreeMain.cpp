#include <iostream>
#include "BinaryTree.hpp"
using namespace std;

void add(BinaryTree* binTree) {
    node* prnt = nullptr;
    int n, prnt_val;
    char ch;
    cout << "Add left or right? (l/r): ";
    cin >> ch;
    ch = tolower(ch);

    if (ch != 'l' && ch != 'r') {
        cout << "Invalid input\n";
    }

    cout << "Select a parent: ";
    cin >> prnt_val;
    prnt = binTree->search(prnt_val);
    if(!prnt) {
        cout << "Parent not found" << endl;
    }

    cout << "Enter the child to be added: ";
    cin >> n;

    if(ch == 'l'){
        binTree->addLeft(prnt, n);
    }else{
        binTree->addRight(prnt, n);
    }
}

int main(){
    BinaryTree* binTree = new BinaryTree();
    BinaryTree* b1 = new BinaryTree();
    BinaryTree* b2 = new BinaryTree();
    node* prnt = nullptr;
    int n, prnt_val;
    char op, ch;
        do{
            cout << "Op: ";
            cin >> op;

            switch(op){
                case 'a':
                    add(binTree);
                    break;
                case 'r':
                    try {
                        cout << "Enter root: ";
                        cin >> n;
                        binTree->addRoot(n);
                    } catch (exception& e){
                        cout << e.what() << endl;
                    }
                    break;
                case 'R':
                    cout << "Enter value of node: ";
                    cin >> n;
                    binTree->remove(binTree->search(n));
                
                    break;
                case 's':
                    cout << "Get sibling of? ";
                    cin >> n;
                    cout << binTree->sibling(binTree->search(n))->elem << " is the sibling of " << n << endl;
                    break;
                case 'p':
                    cout << "----------------------" << endl;
                    binTree->print();
                    cout << "----------------------" << endl;
                    break;
                case 'P':
                    binTree->preorder();
                    break;
                case 'I':
                    binTree->inorder();
                    break;
                case 'O':
                    binTree->postorder();
                    break;
                case 'B':
                    binTree->breadthFirst();
                    break;
                case 'x':
                    cout << "Exiting..." << endl;
                    break;
                case '+':
                    cout << "Which node to attach?" << endl;
                    cin >> prnt_val;
                    prnt = binTree->search(prnt_val);
                    if(!prnt) {
                        cout << "Node not found" << endl;
                        break;
                    }

                    cout << "Add input to Tree 1:" << endl;
                    add(b1);
                    cout << "Add input to Tree 2:" << endl;
                    add(b2);

                    binTree->attach(prnt, b1, b2);
                    cout << "Successfully Attached" << endl;

                default:
                    cout << "----------------------" << endl;
                    cout << "Invalid operation" << endl;
                    cout << "----------------------" << endl;
                    break;
            }
        }while(op != 'x');
    
}
