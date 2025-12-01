#include <iostream>
using namespace std;

struct node{
    int elem;
    node* next;
};

class CircularLL {
    int size;
    node* tail;

    public: 
    CircularLL(){
        size = 0;
        tail = nullptr;
    }

    // void addFirst(int n){
    //     node* newNode = new node{n, nullptr};
    //     if(tail == nullptr){
    //         tail = newNode;
    //         tail->next = tail;
    //     }else{
    //         newNode->next = tail->next;
    //         tail->next = newNode;
    //     }
    //     size++;
    // }

    void addFirst(int n){
        node* newNode = new node{n, nullptr};
        if(!tail){
            tail = newNode;
            tail->next = tail;
        }else{
            newNode->next = tail->next;
            tail->next = newNode;
        }
        size++;
    }

    // void addLast(int n){
    //     node* newNode = new node{n, nullptr};
    //     if(tail == nullptr){
    //         tail = newNode;
    //         tail->next = newNode;
    //     }else{
    //         newNode->next = tail->next;
    //         tail->next = newNode;
    //         tail = newNode;
    //     }
    //     size++;
    // }

    void addLast(int n){
        node* newNode = new node{n, nullptr};
        if(!tail){
            tail = newNode;
            tail->next = tail;
        }else{
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insert(int pos, int n){
        if(pos < 1 || pos > size + 1) return;
        if(pos == 1){
            addFirst(n);
            return;
        }
        if(pos == size + 1){
            addLast(n);
            return;
        }
        
        node* curr = tail->next;
        
        for(int i = 0; i<pos; i++){
            curr = curr->next;
        }
        node* newNode = new node{n, curr->next};
        curr->next = newNode;
        size++;
    }

    void print(){
        if(!tail->next){
            cout << "EMPTY" << endl;
            return;
        }
        int i = 0;
        do{
            rotate();
            cout << tail->elem;
            if(i < size){
                cout << " -> ";
            }
            i++;
        }while(i <= size);

        cout << endl;
    }

    void rotate(){
        // if (!tail->next || tail->next == tail) return;
        // tail->next = tail->next->next;
        // tail = tail->next;
        if(tail != nullptr){
            tail = tail->next;
        }
    }

    // void rotates() {
    //     if (tail == nullptr || tail->next == tail) return;
        
    //     node* curr = tail->next; 
    //     while (curr->next != tail) {
    //         curr = curr->next;
    //     }

    //     tail = curr;
    // }

    void rotates(){
        node* curr = tail->next;
        while(curr->next != tail){
            curr = curr->next;
        }

        tail = curr;
    }

    // int removeNode(int n) {
    //     if(!tail) return 0;
    //     node* curr = tail->next;
    //     node* prev = tail;
    //     int ctr = 0;

    //     do{
    //         ctr++;
    //         if(curr->elem == n){
    //             if(size == 1){
    //                 delete curr;
    //                 tail = nullptr;
    //             // }else if(curr == tail){
    //             //     prev->next = tail->next;
    //             //     tail = prev;
    //             //     delete curr;
    //             // }else if(curr == tail->next){
    //             //     tail->next = curr->next;
    //             //      delete curr;
    //             }else{
    //                 prev->next = curr->next;
    //                 delete curr;
    //             }
    //             size--;
    //             return ctr;
    //         }
    //         prev = curr;
    //         curr = curr->next;
            
    //     }while(curr != tail->next);
    //     return 0;
    // } 

    int removeNode(int pos){
        if(!tail) return -1;
        node* curr = tail->next;
        node* prev = tail;
        int ctr = 0;

        do{
            ctr++;
            if(ctr == pos){
                if(size == 1){
                    delete curr;
                    tail = nullptr;
                }else{
                    prev->next = curr->next;
                    delete curr;
                }
                size--;
                return ctr;
            }
            prev = curr;
            curr = curr->next;
        }while(curr != tail);
        return -1;
    }
    
};