#include <iostream>
#include "myGenTree.hpp"
using namespace std;

int main(){
    GenTree* tree = new MyGenTree();
    Node* prnt = nullptr;
    int n, prnt_val;
    char op;
        do{
            cout << "Op: ";
            cin >> op;

            switch(op){
                case 'a':
                    if(tree->getSize() == 0){
                        cout << "Tree is empty" << endl;
                        break;
                    }
                    cout << "----------------------" << endl;
                    tree->print();
                    cout << "----------------------" << endl;
                    cout << "Select a parent: ";
                    cin >> prnt_val;

                    cout << "Enter the child to be added: ";
                    cin >> n;
                    cout << "----------------------" << endl;
                    prnt = tree->getNode(prnt_val);
                    if(!prnt) {
                        cout << "Parent not found" << endl;
                        cout << "----------------------" << endl;
                        break;
                    }
                    tree->addChild(prnt, n);
                    break;
                case 'r':
                    try {
                        cout << "----------------------" << endl;
                        cout << "Enter root: ";
                        cin >> n;
                        tree->addRoot(n);
                    } catch (exception& e){
                        cout << e.what() << endl;
                    }
                    cout << "----------------------" << endl;
                    break;
                case 'p':
                    cout << "----------------------" << endl;
                    tree->print();
                    cout << "----------------------" << endl;
                case 'x':
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "----------------------" << endl;
                    cout << "Invalid operation" << endl;
                    cout << "----------------------" << endl;
                    break;
            }
        }while(op != 'x');

    
}