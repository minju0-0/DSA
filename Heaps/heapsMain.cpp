#include <iostream>
#include "MyHeap.hpp"
using namespace std;

int main() {
    Heap* heap = new MyHeap();
    int n;
    char op;

    do {
        cout << "Op: ";
        cin >> op;
        switch (op) {
            case 'i':
                cin >> n;
                try {
                    heap->heapPush(n);
                }catch (exception& e) {
                    cout << e.what() << endl;
                }
                break;
            case 'r':
                try {
                    cout << "Removed: " << heap->heapPop() << endl;
                }catch (exception& e) {
                    cout << e.what() << endl;
                }
                break;
            case 'p':
                heap->print();
                break;
            case 'x':
                cout << "Exiting..." << endl;
                break;
            default: cout << "invalid input" << endl;
        }
    }while (op != 'x');

    return 0;
}