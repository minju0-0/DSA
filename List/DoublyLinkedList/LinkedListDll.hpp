#include <iostream>
#include "DllList.hpp"
#include "Dllnode.hpp"
using namespace std;



class DLinkedList : public List {
    int size = 0;

    // Dummy Nodes / Sentinel
    Node head, tail;

    Node* addBetween(int num, Node* pred, Node* succ){
        Node* newNode = new Node{num, succ, pred};
        pred->next = newNode;
        succ->prev = newNode;
        size++;

        return newNode;
    }

    int removeNode(Node* n){
        int res = n->data;
        n->prev->next = n->next;
        n->next->prev = n->prev;
        delete(n);
        size--;
        
        return res;
    }

    Node* getNode(int pos) {
        if(pos > size|| pos < 1) return nullptr;

        Node* curr = head.next;
        for(int i = 1; i<pos; i++){
            curr = curr->next;
        }

        return curr;
    }


    public: 

    DLinkedList() {
        size = 0; 

        head.next = &tail;
        head.prev = nullptr;

        tail.prev = &head;
        tail.next = nullptr;
        
    }

    ~DLinkedList(){
        Node* curr = head.next;
        while(curr != &tail){
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    //add tail
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
        if(pos > size + 1 || pos < 1){
            cout << "Invalid position" << endl;
            return;
        }

        if(pos == size + 1) {
            add(num);
            return;
        }
        
        Node* curr = &head;
        for(int i = 1; i<pos; i++){
            curr = curr->next;
        }

        addBetween(num, curr, curr->next);
        return;
    }

    //seatwork quiz
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
        Node* toDelete = getNode(pos);
        if(!toDelete) {
            return -1;
        }
        return removeNode(toDelete);
    }

    int removeAll(int num){
        int count = 0;
        Node* curr = head.next;
        while(curr != &tail){
            if(curr->data == num){
                Node* toDelete = curr;
                curr = curr->next;
                removeNode(toDelete);
                count++;
            } else {
                curr = curr->next;
            }
        }

        return count;
    }

    int getPosition(int num) {
        Node* curr = head.next;
        for(int i = 1; i<=size; i++){
            if(curr->data == num){
                return i;
            }
            curr = curr->next;
        }

        return -1;
    }
};  