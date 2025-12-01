#include <iostream>
#include <cmath>
using namespace std;

class Stack {
    int size;
    int* arr;
    int cap;

    public:
    Stack(){
        size = 0;
        cap = 5;
        arr = (int*)malloc(cap * sizeof(int));
    }

    void push(int n){
        if(size > ceil(cap * 0.6)){
            cap += ceil(cap * 0.5);
            arr = (int*)realloc(arr, cap * sizeof(int));
        }

        arr[size++] = n;
    }

    int pop(){
        if(size == 0) return -1;
        int res = arr[size - 1];
        
        if(size <= floor(cap * 0.5)){
            cap -= floor(cap * 0.6);
            arr = (int*)realloc(arr, cap * sizeof(int));
        }
        size--;
        return res;
    }

    int top(){
        if(size == 0) return -1;
        return arr[size - 1];
    }

    int isEmpty(){
        return size == 0;
    }

    void print(){
        if(size == 0){
            cout << "EMPTY";
        }

        cout << "Stack: ";
        for(int i = 0; i<size; i++){
            cout << arr[i] << " ";
        }
    }

    int getSize(){
        return size;
    }
};