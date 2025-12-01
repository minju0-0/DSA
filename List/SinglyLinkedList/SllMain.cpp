#include <iostream>
#include "LinkedListSll.hpp"
using namespace std;

int main(){

    List *list = new SLinkedList();
    char op;
    int n, pos;

    do{
        cout << "OP: ";
        cin >> op;

        switch(op){
            case 'a':
                cin >> n;
                list->addTail(n);
                break;
            case 'A':
                cin >> n;
                list->addHead(n);
            case 'p':
                list->print();
                break;
            case 't':
                cin >> pos;
                {
                    int removed = list->removeAt(pos);
                    if (removed == -1) {
                        cout << "Invalid Position" << endl;
                    } else {
                        cout << "Removed " << removed << endl;
                    }
                }
                break;
            case 'g':
                cin >> n;
                {
                    int nPos = list->getPosition(n);
                    if(nPos == -1){
                        cout << "Element not found" << endl;
                    }else{
                        cout << "Element is in position " << nPos << endl;
                    }
                }
                break;
            case 'r':
                cin >> n;
                cout << "Removed position " << list->remove(n) << endl;
                break;
            case '@':
                cin >> n;
                cin >> pos;
                list->addAt(n, pos); 
                break;
            case 'x':
                cout << "Exiting..." << endl;
                break;
            case 'R' :
                cin >> n;
                cout << "Removed " << list->removeAll(n) << " element/s of \"" << n <<"\"" << endl;
                break;
            
            default:
                cout << "Invalid operation" << endl;
            
        }
    }while(op != 'x');
}