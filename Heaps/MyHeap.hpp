#include <cmath>
#include <iostream>
#include <algorithm>
#include "Heap.hpp"
using namespace std;

class MyHeap : public Heap {
    int size;
    int cap;
    int *arr;
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


    string makeSpace(int num, string str){
            string res = "";
            for(int i = 0; i < num; i++){
                res += str;
            }
            return res;
        }

    void printGrid(){
            if(size == 0){
                cout << "Empty" << endl;
                return;
            }

            int height = floor(log2(size));
            int newSize = pow(2, height);

            cout << makeSpace(pow(2, height), "------") << endl;

            int count = 1;
            cout << makeSpace(pow(2, height) - 1, "   ") << arr[0] << endl;

            for(int i = 1; i <= height; i++){
                int copy = count;
                cout << makeSpace(pow(2, height - i) - 1, "   ");
                for(int j = 0; j < pow(2, i); j++){
                    string arrow = "/";
                    if(copy % 2 == 0){
                        arrow = "\\";
                    }
                    if(copy >= size){
                        arrow = " ";
                    }
                    cout << " " << arrow << " " << makeSpace(pow(2, height - (i - 1)) - 1, "   ");
                    copy++;
                }
                cout << endl;

                cout << makeSpace(pow(2, height - i) - 1, "   ");

                for(int j = 0; j < pow(2, i); j++){
                    string space = " ";
                    int str = arr[count];
                    if(count < size){
                        int str = arr[count];
                        if(str > 9){
                            space = "";
                        }
                        cout << " " << str << space << makeSpace(pow(2, height - (i - 1)) - 1, "   ");
                    } else {
                        cout << "   " << makeSpace(pow(2, height - (i - 1)) - 1, "   ");
                    }
                    count++;
                }
                cout << endl;

            }
            cout << makeSpace(pow(2, height), "------") << endl;
        }

    int leftIndex(int parentIndex) { return parentIndex * 2 + 1; }

    int rightIndex(int parentIndex) { return parentIndex * 2 + 2; }

    int parentIndex(int childIndex) { return (childIndex - 1) / 2; }

    public:
    MyHeap() {
        size = 0;
        cap = 5;
        arr = new int[5];
    }

    void print() {
        if (size == 0) {
            cout << "Empty Heap" << endl;
            return;
        }
        cout << "Size: " << size << endl;
        printGrid();
    }

    
};
