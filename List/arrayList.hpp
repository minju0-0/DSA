#include <iostream>
#include "List.hpp"
using namespace std;

class arrayList : public List{
    
    private:
    int size = 0;
    int arr[100];   

    public:
    void add(int num){
        if(size >= 100){
            cout << "Cannot add" << endl;
            return;
        }
        cout << "Adding " << num << "..." << endl;
        arr[size++] = num;
    }

    int n = sizeof(arr) / sizeof(arr[0]);

    void removeAt(int pos){
        if(pos > size){
            cout << "List is full" << endl;
        }else{
            cout << "Removing at position " << pos << "..." << endl;
            for(int i = pos - 1; i<size - 1; i++){
                arr[i] = arr[i + 1];
            }
            size--;
        }
    }

     void print(){
        //cout << "(" << size << ")" << endl;
        cout << "Elements of the array: ";
        for(int i = 0; i<size; i++){
            cout << arr[i] << " ";
        }
    }

    void insertAt(int pos, int num){
        size++;
        if(pos > size){
            cout << "Cannot insert, List is full" << endl;
            return;
        }
        cout << "Inserting " << num << " at position " << pos << "..." << endl;
        for(int i = size - 1; i > pos - 1; i--){
            arr[i] = arr[i - 1];
        }
        arr[pos - 1] = num;
    }

    void remove(int num){
        int pos;
        for(int i = 0; i<size; i++){
            if(num == arr[i]){
                pos = i + 1;
                break;
            }
        }

        if(pos > size){
            cout << "List is full" << endl;
        }else{
            cout << "Removing at position " << pos << "..." << endl;
            for(int i = pos - 1; i<size - 1; i++){
                arr[i] = arr[i + 1];
            }
            size--;
        }
    }



};