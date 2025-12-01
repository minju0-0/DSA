#include "BSTree.hpp"
#include <iostream>
using namespace std;

int main() {
    BST* bst = new BSTree();
    node* temp;
    char op;
    int n;
        do{
            cout << "Op: ";
            cin >> op;

            switch(op){
                case 'a':
                    try {
                        cout << "Enter value to insert: ";
                        cin >> n;
                        bst->insert(n);
                    } catch (exception& e) {
                        cout << e.what() << endl;
                    }
                    break;
                case 'r':
                    cout << "Enter value to remove: ";
                    cin >> n;
                    try {
                        cout << "Removed " << bst->remove(n) << endl;
                    } catch (exception& e) {
                        cout << -1 << " " << e.what() << endl;
                    }
                    break;
                case 's':
                    cout << "Enter value to search: ";
                    cin >> n;
                    temp = bst->search(n);
                    if (!temp) cout << "Element not found" << endl;
                    else cout << temp->elem << "(it exists)" << endl;
                    break;
                case 'p':
                    cout <<"----------------------" << endl;
                    bst->print();
                    cout << endl <<  "----------------------" << endl;
                    break;
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