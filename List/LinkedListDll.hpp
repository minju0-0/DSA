#include <iostream>
#include "List.hpp"
using namespace std;

struct Node{
    int data;
    Node* next;
    Node* prev;

};

class DLinkedList : public List {
    int size = 0;

    Node head, tail;

    Node* addBetween(int num, Node* pred, Node* succ){
        Node* newNode = new Node{num, succ, pred};
        pred->next = newNode;
        succ->prev = newNode;
        size++;

        return newNode;
    }

    private: 
    int removeNode(Node* n){
        int res = n->data;
        n->prev->next = n->next;
        n->next->prev = n->prev;
        free(n);
        size--;
        
        return res;
    }


    public: 

    DLinkedList() {
        size = 0; 

        head.next = &tail;
        head.prev = nullptr;

        tail.prev = &head;
        tail.next = nullptr;
        
    }

    void add(int num){
        addBetween(num, tail.prev, &tail);
    }

    void print(){
        if(size == 0){
            cout << "Empty" << endl;
            return;
        }
        Node* curr = head.next;
        cout << "From Head: " << endl;
        while(curr != &tail){
            cout << curr->data << " -> ";
            curr = curr->next; 
        }
        cout << endl;

        curr = tail.prev;
        cout << "From Tail: " << endl;
        while(curr != &head){
            cout << curr->data << " -> ";
            curr = curr->prev; 
        }
        cout << endl;
    }

    void addAt(int num, int pos){
        if(pos > size || pos < 1){
            cout << "Invalid position" << endl;
            return;
        }
        Node* curr = head.next;
        for(int i = 1; i<pos - 1; i++){
            curr = curr->next;
        }

        addBetween(num, curr, curr->next);
        return;
    }

    void addMid(int num){
        if(size == 0){
            addBetween(num, &head, &tail);
            return;
        }
        Node* curr = head.next;
        for(int i = 1; i< size / 2; i++){
            curr = curr->next;
        }
        addBetween(num, curr, curr->next);
        return;
    }

    int remove(int num){
        Node* curr = head.next;
        for(int i = 1; i<=size; i++){
            if(curr->data == num){
                removeNode(curr);
                return i;
            }
            curr = curr->next;
        }
        return -1;
    }

    int removeAt(int pos) {
        Node* curr = head.next;
        for(int i = 0; i<pos; i++){
            curr = curr->next;
        }

        return removeNode(curr);


    }
};  