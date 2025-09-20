#include <iostream>
#include "List.hpp"
#include "node.hpp"
using namespace std;

class LinkedList : public List {
    Node *head = nullptr;
    Node *tail = nullptr;
    int size = 0;


    public: 

    LinkedList() {
        size = 0; 
        head = nullptr;
        tail = nullptr;
    }

    void add(int n){
        Node *newNode = new Node{n, nullptr};
        if(!head) head = tail = newNode;
        else tail = tail->next = newNode;
        size++;
    }

    void print() {
        Node* temp = head;
        while(temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }

    void addAtHead(int n){
        Node* newNode = new Node{n, head};
        head = newNode;
        if(size == 0) tail = newNode;
        size++;
    }

    void addAtTail(int n){
        Node* newNode = new Node{n, nullptr};
        if(!head) addAtHead(n);
        else{
            tail->next = newNode;
            tail = newNode;
            size++;
        }
    }

    int getPosition(int n) {
        Node* temp = head;
        for(int i = 0; temp != nullptr && i<size; i++){
            if(temp->data == n) return i+1;
            temp = temp->next;
        }

        return -1;
    }

   void removeHead() {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;

        
   }

   void removeTail() {
        Node* curr = head;
        while(curr->next != tail){
            curr = curr->next;
        }

        delete tail;
        tail = curr;
        tail->next = nullptr;
        size--;

   }

   int remove(int n) {
        if(!head) return 0;
        if(head->data == n) {
            removeHead();
            return 1;
        }
        if(tail->data == n){
            removeTail();
            return 1;
        }

        Node* front, *back;
        front = head->next;
        while(front){
            if(front->data == n){
                back->next = front->next;
                delete front;
                size--;
                return 1;
            }
            back = front;
            front = front->next;
        }
        return 0;
   }

   int addAt(int n, int pos){
        if(!head) return 0;
        if(pos > size && pos < size) return 0;
        if(pos == 1){
            addAtHead(n);
            return 1;
        }
        if(pos - 1 == size){
            addAtTail(n);
            return 1;
        }

        Node* curr = head;
        for(int i = 0; i<pos - 2; i++){
            curr = curr->next;
        }

        Node* newNode = new Node{n, curr->next};
        curr->next = newNode;
        size++;
        return 1;

   }

   int removeAll(int n){
        int count = 0;
        if(!head) return 0;
        while(head && head->data == n) {
            removeHead();
            count++;
        }
        
        Node* curr = head;
        while(curr && curr->next){
            if(curr->next->data == n){
                Node* toDelete = curr->next;
                curr->next = toDelete->next;
                if(toDelete == tail) tail = curr;
                delete toDelete;
                count++;
                size--;
            }else{
                curr = curr->next;
            }
        }
        return count;
   }


};  